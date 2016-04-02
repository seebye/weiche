#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "header/path.hpp"

// Weiche - Bahn :					eine Spur -> mehrere Spuren
//									ein Event -> mehrere Events
#define PROGNAME					"weiche"
#define VERSION						"1.0.0"

//grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 'EV=120013' | grep -Eo 'event[0-9]+'
#define DEV_INPUT					"/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#define KEYBINDINGS					(getDirHome()+"/.config/"+ PROGNAME +"/keybindings")

#define PRESS_LONG_REPEAT_MS		1800
#define PRESS_LONG_REPEAT_PERIOD_MS	500
#define PRESS_LONG_MS				1200
#define PRESS_DBL_MS				300

#endif
