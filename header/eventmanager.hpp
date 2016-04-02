#ifndef __EVENTMANAGER_HPP__
#define __EVENTMANAGER_HPP__

#include "header/basic.hpp"
#include <string>
#include <set>
#include <functional>
#include <mutex>
#include "header/events.hpp"
#include "header/delayedexecutor.hpp"
#include "header/device.hpp"

using namespace std;

#define EV_FLAG_INSTANTLYCONSUME	0b1
#define EV_FLAG_VERBOSE				0b10

enum EventAction {
	CONSUMED,
	PASS_THROUGH
};

class EventManager {
private:
	bool m_bInstantlyConsume;
	bool m_bVerbose;
	set<ushort> m_unconsumedKeys;

	function<void(set<ushort>)> m_cbExecuted;
	function<void(set<ushort>)> m_cbExecuted_NoMtx;
	mutex* m_mtx;
	set<ushort> m_setPressed;
	map<set<ushort>, DelayedExecutor*> m_mapPending;
	map<set<ushort>, map<Event, string>> m_mapKeybindings;
	long m_lStarted;
	long m_lNextPressLong;
	short m_nCountPressLong;

	bool m_bRun;

	Device* m_out;
	Device* m_in;

	static set<ushort> s_allowedKeyCodes;

protected:
	EventAction	onPress(ushort code);
	void onPressing(ushort code);
	void onRelease(ushort code);
	bool isAlwaysPassed(ushort code);

public:
	EventManager(string strDevicePath, string strKbPath, int nFlags);
	~EventManager();
	void process_queue();
	void stop();
};


#endif