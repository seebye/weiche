#include <iostream>

#include "header/basic.hpp"
#include "header/keys.hpp"
#include "header/eventmanager.hpp"
#include "header/events.hpp"
#include "header/loader.hpp"
#include "header/config.hpp"


set<ushort> EventManager::s_allowedKeyCodes {
	KEY_LEFTMETA, KEY_RIGHTMETA,
	KEY_LEFTCTRL, KEY_RIGHTCTRL,
	KEY_LEFTSHIFT, KEY_RIGHTSHIFT,
	KEY_LEFTALT, KEY_RIGHTALT
};

EventManager::EventManager(string strDevicePath, string strKbPath, int nFlags)
	: m_mtx(new mutex()),
	  m_mapKeybindings(loadKeybindings(strKbPath)),
	  m_lStarted(0), m_bRun(true) {
	m_bInstantlyConsume = (nFlags & EV_FLAG_INSTANTLYCONSUME) != 0;
	m_bVerbose = (nFlags & EV_FLAG_VERBOSE) != 0;

	m_out = new Device("/dev/uinput", O_WRONLY | O_NONBLOCK);
	m_in = new Device(strDevicePath.c_str(), O_RDWR);

  	m_cbExecuted = [this](set<ushort> setPressed) {
  		//cout<<"waiting.."<<endl;
		lock_guard<mutex> lock(*this->m_mtx);
		//cout<<"in.."<<endl;
  		DelayedExecutor* executor = m_mapPending[setPressed];
		m_mapPending.erase(setPressed);
		delete executor;
		executor = nullptr;
			//cout << "pending : " << mapPending.size() << endl;
  	};
  	m_cbExecuted_NoMtx = [this](set<ushort> setPressed) {
  		DelayedExecutor* executor = m_mapPending[setPressed];
		m_mapPending.erase(setPressed);
		delete executor;
		executor = nullptr;
			//cout << "pending : " << mapPending.size() << endl;
  	};
}

EventManager::~EventManager() {
	delete m_out;
	delete m_in;
	delete m_mtx;
	m_out = nullptr;
	m_in = nullptr;
	m_mtx = nullptr;
}


EventAction	EventManager::onPress(ushort code) {
	lock_guard<mutex> lock(*m_mtx);
	if(contains(m_mapPending, m_setPressed)) {
		// additional key was pressed
		// remove keys from our list
		m_cbExecuted_NoMtx(m_setPressed);
	}

	m_setPressed.insert(code);
	m_lStarted = timestampms().count();
	m_lNextPressLong = timestampms().count()
					 + PRESS_LONG_REPEAT_MS;
	m_nCountPressLong = 0;

	if(contains(m_mapKeybindings, m_setPressed)
		&& !contains(m_mapPending, m_setPressed)) {
		DelayedExecutor* executor = new DelayedExecutor(m_setPressed,
														m_mapKeybindings[m_setPressed][EVENT_PRESS],
														m_mapKeybindings[m_setPressed][EVENT_PRESS_LONG],
														m_mapKeybindings[m_setPressed][EVENT_PRESS_DBL],
														contains(m_mapKeybindings[m_setPressed], EVENT_PRESS_LONG_REPEAT),
														m_cbExecuted);
		m_mapPending[m_setPressed] = executor;

		// key combination is on our list
		// -> consume
		return CONSUMED;
	}

	return PASS_THROUGH;
}

void EventManager::onPressing(ushort code) {
	lock_guard<mutex> lock(*m_mtx);
	if(timestampms().count() - m_lStarted > PRESS_LONG_REPEAT_MS
		&& m_lNextPressLong <= timestampms().count()
		&& contains(m_mapPending, m_setPressed)) {
		m_mapPending[m_setPressed]->repeat();
		m_nCountPressLong++;
		m_lNextPressLong = timestampms().count()
						 + max<long>(PRESS_LONG_REPEAT_PERIOD_MS * (15.0-m_nCountPressLong)/15.0, 0);
	}
}

void EventManager::onRelease(ushort code) {
	lock_guard<mutex> lock(*m_mtx);
	// avoid crashs by manual starts (e.g. releasing y)
	// code is likly to be not in the list
	if(contains(m_setPressed, code)) {

		if(contains(m_mapPending, m_setPressed)) {
			if(m_mapPending[m_setPressed]->isRunning()) {
				// execute double press
				m_mapPending[m_setPressed]->dbl_press();
			}
			else {//if(!bNeedsPress) {
				// start the execution of long press & single press
				m_mapPending[m_setPressed]->start(timestampms().count() - m_lStarted);
			}
		}

		m_setPressed.erase(code);
	}
}

void EventManager::stop() {
	m_bRun = false;
	m_in->passthrough();
}

bool EventManager::isAlwaysPassed(ushort code) {
	return contains(s_allowedKeyCodes, code);
}

void EventManager::process_queue() {
	struct input_event event;

	m_out->reg_keyboard();

	if(m_bInstantlyConsume && m_bRun) {
		m_in->consume();
	}

	while(m_bRun) {
		event = m_in->read();

		if(!m_in->isConsuming()
			&& event.type == EV_KEY
			&& event.value == EVENT_SYSTEM_RELEASE) {
			m_in->consume();
		}
		else if(m_in->isConsuming()) {
			if(event.type == EV_KEY) {
				if(m_bVerbose) {
					cout << "[" << event.code << "] "
						 << typeString(static_cast<KeyCode>(event.code))
						 << " " << event.value << endl;
				}

				switch(event.value) {
					case EVENT_SYSTEM_PRESS:
						if(onPress(event.code) != CONSUMED) {
							m_unconsumedKeys.insert(event.code);
						}
						break;
					case EVENT_SYSTEM_PRESSING:
						onPressing(event.code);
						break;
					case EVENT_SYSTEM_RELEASE:
						onRelease(event.code);
						break;
				}
			}

			if(event.type != EV_KEY
				|| contains(m_unconsumedKeys, event.code)
				|| isAlwaysPassed(event.code)) {
				m_out->write(event.type, event.code, event.value);

				if(event.value == EVENT_SYSTEM_RELEASE) {
					m_unconsumedKeys.erase(event.code);
				}
				if(event.type == EV_KEY) {
					// force sync - avoid laggs
					m_out->write(EV_SYN, SYN_REPORT, 0);
				}
			}
		}
	}
}