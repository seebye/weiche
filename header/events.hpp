#ifndef __EVENTS_HPP__
#define __EVENTS_HPP__

#include <string>
#include <map>

using namespace std;

#define EVENT_SYSTEM_RELEASE	0
#define EVENT_SYSTEM_PRESS	1
#define EVENT_SYSTEM_PRESSING	2

#define EVENT_TYPE_KEY		1

//see: http://journal.stuffwithstuff.com/2012/01/24/higher-order-macros-in-c/

#define EVENT_LIST(code)	\
	code(EVENT_UNKNOWN)	\
	code(EVENT_PRESS)	\
	code(EVENT_PRESS_LONG)	\
	code(EVENT_PRESS_DBL)	\
	code(EVENT_PRESS_LONG_REPEAT)

#define DEFINE_ENUM_TYPE(type) type,
enum Event {
	EVENT_LIST(DEFINE_ENUM_TYPE)
};
#undef DEFINE_ENUM_TYPE

Event getEvent(string strText);
string typeString(Event event);

#endif
