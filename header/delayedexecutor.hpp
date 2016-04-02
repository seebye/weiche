#ifndef __DELAYEDEXECUTOR_H__
#define __DELAYEDEXECUTOR_H__

#include <set>
#include <map>
#include <string>
#include <functional>
#include <mutex>
#include "basic.hpp"
#include "events.hpp"

using namespace std;


class DelayedExecutor {
private:
	bool m_bInterrupted;
	bool m_bRunning;
	set<ushort> m_setKeys;
	long m_lPressedMs;
	//map<Event, string>& m_mapActions;
	string m_strCmd_Press;
	string m_strCmd_PressLong;
	string m_strCmd_PressDbl;
	function<void(set<ushort>)> m_cbExecuted;

	bool isSupported(Event event);
	void execute_unfinished(Event event);
	void execute(Event event);
	string getCommand(Event event);
public:
	DelayedExecutor(set<ushort> setKeys,
			//map<Event, string>& mapActions,
			string strCmd_Press,
			string strCmd_PressLong,
			string strCmd_PressDbl,
			function<void(set<ushort>)> cbExecuted);

	void interrupt();
	void dbl_press();
	void operator()();
	void executed();
	void start(long lPressedMs);
	bool isRunning();
	void repeat();
};

#endif
