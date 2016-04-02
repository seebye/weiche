#include "header/events.hpp"

#define DEFINE_MAP_ENTRY(type) {#type, type},
map<string, Event> MAP_EVENTS {
	//{"EVENT_PRESS",		EVENT_PRESS},
	EVENT_LIST(DEFINE_MAP_ENTRY)
};
#undef DEFINE_MAP_ENTRY

Event getEvent(string strText) {
	if(MAP_EVENTS.find(strText) == MAP_EVENTS.end()) {
		return EVENT_UNKNOWN;
	}
	return MAP_EVENTS[strText];
}

#define DEFINE_SWITCH_ENTRY(type) case type: return #type;
string typeString(Event event) {
	switch(event) {
		EVENT_LIST(DEFINE_SWITCH_ENTRY)
	}
	return "null";
}
#undef DEFINE_SWITCH_ENTRY
