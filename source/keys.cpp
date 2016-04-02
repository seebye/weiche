#include "header/keys.hpp"



#define DEFINE_MAP_ENTRY(type, value) {#type, static_cast<KeyCode>(value)},
map<string, KeyCode> MAP_KEYCODES {
	KEYCODE_LIST(DEFINE_MAP_ENTRY)
};
#undef DEFINE_MAP_ENTRY

KeyCode getKeyCode(string strText) {
	if(MAP_KEYCODES.find(strText) == MAP_KEYCODES.end()) {
		return KEY_UNKNOWN;
	}
	return MAP_KEYCODES[strText];
}

#define DEFINE_SWITCH_ENTRY(type, value) case value: return #type;
string typeString(KeyCode code) {
	switch(static_cast<int>(code)) {
		KEYCODE_LIST(DEFINE_SWITCH_ENTRY)
	}
	return "null";
}
#undef DEFINE_SWITCH_ENTRY
