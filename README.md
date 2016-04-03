#Weiche
This is a key event handler which allows you to bind multiple commands to the same key combination.  
It interprets the key events and creates three different types of events.  

1. Press  
2. Long Press
3. Double Press

**Warning:**  
The "-i" option could lead to problems.  
(Permanent pressed keys after killing weiche)

## Libraries

1. [JSONXX](https://github.com/hjiang/jsonxx)

## Dependencies

Your system needs to support the /dev/uinput device.  

## Installation

```bash
$ make
$ sudo make install
```

##Usage

```bash
usage: weiche [option]

Options
    -h --help           Shows this message
    -d --verbose        Displays events
    -v --version        Print program version
    -i --instantly      Consume events instantly 
    -r --device         Input device, default: 
                        /dev/input/by-path/platform-i8042-serio-0-event-kbd
    -k --kbpath         Path keybindings, default: 
                        /home/[user]/.config/weiche/keybindings
```

## Config

### KeyCodes  
Weiche uses the names of the KeyCodes from /usr/include/linux/input-event-codes.h

[KeyCodes](https://github.com/seebye/weiche/blob/master/header/keys.hpp)

### Examples  

Binding press event

```
[
    {
        KEYS:               ["KEY_LEFTMETA"],
        EVENT_PRESS:        "$HOME/i3/event/super.sh &"
    },
]
```

Binding long - & press event

```
[
    {
        KEYS:               ["KEY_LEFTMETA", "KEY_LEFTCTRL"],
        EVENT_PRESS:        "echo 'press super ctrl' &",
        EVENT_PRESS_LONG:   "echo 'long press super ctrl' &",
    },
]
```

Binding long - & double - & press event

```
[
    {
        KEYS:               ["KEY_SYSRQ"],
        EVENT_PRESS:        "echo 'press print' &",
        EVENT_PRESS_LONG:   "echo 'long press print' &",
        EVENT_PRESS_DBL:    "echo 'double press print' &",
    },
]
```

Repeating the long press command

```
[
    {
        KEYS:               ["KEY_SYSRQ"],
        EVENT_PRESS_LONG:   "echo 'long press print' &",
        REPEAT:             true
    },
]
```