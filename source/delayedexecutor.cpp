#include "header/delayedexecutor.hpp"
#include "header/config.hpp"
#include "header/events.hpp"
#include <stdlib.h>
#include <iostream>
#include <thread>

DelayedExecutor::DelayedExecutor(set<ushort> setKeys,
								//map<Event, string>& mapActions,
								string strCmd_Press,
								string strCmd_PressLong,
								string strCmd_PressDbl,
								BOOL bPressLongRepeat,
								function<void(set<ushort>)> cbExecuted)
	 : m_bInterrupted(false), m_bRunning(false),
	   m_bFinished(false),
	   m_setKeys(setKeys), m_lPressedMs(0),
	   //m_mapActions(mapActions),
	   m_strCmd_Press(strCmd_Press),
	   m_strCmd_PressLong(strCmd_PressLong),
	   m_strCmd_PressDbl(strCmd_PressDbl),
	   m_bPressLongRepeat(bPressLongRepeat),
	   m_cbExecuted(cbExecuted) {
}

void DelayedExecutor::start(long lPressedMs) {
	m_lPressedMs = lPressedMs;
	m_bRunning = true;
	thread(&DelayedExecutor::operator(), this).detach();
}

BOOL DelayedExecutor::isRunning() {
	return m_bRunning;
}

string DelayedExecutor::getCommand(Event event) {
	string strCmd;

	switch(event) {
		case EVENT_PRESS:
			strCmd = m_strCmd_Press;
			break;
		case EVENT_PRESS_LONG:
			strCmd = m_strCmd_PressLong;
			break;
		case EVENT_PRESS_DBL:
			strCmd = m_strCmd_PressDbl;
			break;
		default:
			break;
	}

	return strCmd;
}

BOOL DelayedExecutor::isSupported(Event event) {
	return !getCommand(event).empty();//contains(m_mapActions, event);
}

void DelayedExecutor::interrupt() {
	m_bInterrupted = true;
}

void DelayedExecutor::repeat() {
	if(isSupported(EVENT_PRESS_LONG)
		&& m_bPressLongRepeat) {
		execute_unfinished(EVENT_PRESS_LONG);
	}
}

/**
* Execute without removing from pending list
*/
void DelayedExecutor::execute_unfinished(Event event) {
	interrupt();
	system(getCommand(event).c_str());//m_mapActions[event].c_str());
}

void DelayedExecutor::execute(Event event) {
	execute_unfinished(event);
	executed();
}

void DelayedExecutor::dbl_press() {
	if(isSupported(EVENT_PRESS_DBL)) {
		execute_unfinished(EVENT_PRESS_DBL);
	}
}

void DelayedExecutor::executed() {
	m_bFinished = true;
	m_cbExecuted(m_setKeys);
}

void DelayedExecutor::operator()() {
	// long pressed && not repeated && supported
	if(m_lPressedMs >= PRESS_LONG_MS
		&& (!m_bPressLongRepeat || m_lPressedMs <= PRESS_LONG_REPEAT_MS)
		&& isSupported(EVENT_PRESS_LONG)) {
		// (single) long press
		execute(EVENT_PRESS_LONG);
	}
	else if(m_lPressedMs <= PRESS_LONG_MS
			|| !isSupported(EVENT_PRESS_LONG)) {
		// no long press or long press not supported
		if(isSupported(EVENT_PRESS_DBL)) {
			sleepms(PRESS_DBL_MS);
		}
	}

	if(!m_bInterrupted
		&& isSupported(EVENT_PRESS)) {
		execute(EVENT_PRESS);
	}
	else if(!m_bFinished) {
		// EVENT_PRESS_LONG multiple times executed
		// or dbl_press executed
		// or press not supported
		executed();
	}
}
