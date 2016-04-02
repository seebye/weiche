#ifndef __KEYS_HPP__
#define __KEYS_HPP__

#include <string>
#include <map>

using namespace std;

#define KEYCODE_LIST(code)		\
	code(KEY_UNKNOWN, -1)		\
	code(KEY_RESERVED, 0)		\
	code(KEY_ESC, 1)			\
	code(KEY_1, 2)				\
	code(KEY_2, 3)				\
	code(KEY_3, 4)				\
	code(KEY_4, 5)				\
	code(KEY_5, 6)				\
	code(KEY_6, 7)				\
	code(KEY_7, 8)				\
	code(KEY_8, 9)				\
	code(KEY_9, 10)				\
	code(KEY_0, 11)				\
	code(KEY_MINUS, 12)			\
	code(KEY_EQUAL, 13)			\
	code(KEY_BACKSPACE, 14)		\
	code(KEY_TAB, 15)			\
	code(KEY_Q, 16)				\
	code(KEY_W, 17)				\
	code(KEY_E, 18)				\
	code(KEY_R, 19)				\
	code(KEY_T, 20)				\
	code(KEY_Y, 21)				\
	code(KEY_U, 22)				\
	code(KEY_I, 23)				\
	code(KEY_O, 24)				\
	code(KEY_P, 25)				\
	code(KEY_LEFTBRACE, 26)		\
	code(KEY_RIGHTBRACE, 27)	\
	code(KEY_ENTER, 28)			\
	code(KEY_LEFTCTRL, 29)		\
	code(KEY_A, 30)				\
	code(KEY_S, 31)				\
	code(KEY_D, 32)				\
	code(KEY_F, 33)				\
	code(KEY_G, 34)				\
	code(KEY_H, 35)				\
	code(KEY_J, 36)				\
	code(KEY_K, 37)				\
	code(KEY_L, 38)				\
	code(KEY_SEMICOLON, 39)		\
	code(KEY_APOSTROPHE, 40)	\
	code(KEY_GRAVE, 41)			\
	code(KEY_LEFTSHIFT, 42)		\
	code(KEY_BACKSLASH, 43)		\
	code(KEY_Z, 44)				\
	code(KEY_X, 45)				\
	code(KEY_C, 46)				\
	code(KEY_V, 47)				\
	code(KEY_B, 48)				\
	code(KEY_N, 49)				\
	code(KEY_M, 50)				\
	code(KEY_COMMA, 51)			\
	code(KEY_DOT, 52)			\
	code(KEY_SLASH, 53)			\
	code(KEY_RIGHTSHIFT, 54)	\
	code(KEY_KPASTERISK, 55)	\
	code(KEY_LEFTALT, 56)		\
	code(KEY_SPACE, 57)			\
	code(KEY_CAPSLOCK, 58)		\
	code(KEY_F1, 59)			\
	code(KEY_F2, 60)			\
	code(KEY_F3, 61)			\
	code(KEY_F4, 62)			\
	code(KEY_F5, 63)			\
	code(KEY_F6, 64)			\
	code(KEY_F7, 65)			\
	code(KEY_F8, 66)			\
	code(KEY_F9, 67)			\
	code(KEY_F10, 68)			\
	code(KEY_NUMLOCK, 69)		\
	code(KEY_SCROLLLOCK, 70)	\
	code(KEY_KP7, 71)			\
	code(KEY_KP8, 72)			\
	code(KEY_KP9, 73)			\
	code(KEY_KPMINUS, 74)		\
	code(KEY_KP4, 75)			\
	code(KEY_KP5, 76)			\
	code(KEY_KP6, 77)			\
	code(KEY_KPPLUS, 78)		\
	code(KEY_KP1, 79)			\
	code(KEY_KP2, 80)			\
	code(KEY_KP3, 81)			\
	code(KEY_KP0, 82)			\
	code(KEY_KPDOT, 83)			\
	code(KEY_103RD, 84)			\
	code(KEY_ZENKAKUHANKAKU, 85)\
	code(KEY_102ND, 86)			\
	code(KEY_F11, 87)			\
	code(KEY_F12, 88)			\
	code(KEY_RO, 89)			\
	code(KEY_KATAKANA, 90)		\
	code(KEY_HIRAGANA, 91)		\
	code(KEY_HENKAN, 92)		\
	code(KEY_KATAKANAHIRAGANA, 93)	\
	code(KEY_MUHENKAN, 94)		\
	code(KEY_KPJPCOMMA, 95)		\
	code(KEY_KPENTER, 96)		\
	code(KEY_RIGHTCTRL, 97)		\
	code(KEY_KPSLASH, 98)		\
	code(KEY_SYSRQ, 99)			\
	code(KEY_RIGHTALT, 100)		\
	code(KEY_LINEFEED, 101)		\
	code(KEY_HOME, 102)			\
	code(KEY_UP, 103)			\
	code(KEY_PAGEUP, 104)		\
	code(KEY_LEFT, 105)			\
	code(KEY_RIGHT, 106)		\
	code(KEY_END, 107)			\
	code(KEY_DOWN, 108)			\
	code(KEY_PAGEDOWN, 109)		\
	code(KEY_INSERT, 110)		\
	code(KEY_DELETE, 111)		\
	code(KEY_MACRO, 112)		\
	code(KEY_MUTE, 113)			\
	code(KEY_VOLUMEDOWN, 114)	\
	code(KEY_VOLUMEUP, 115)		\
	code(KEY_POWER, 116)		\
	code(KEY_KPEQUAL, 117)		\
	code(KEY_KPPLUSMINUS, 118)	\
	code(KEY_PAUSE, 119)		\
	code(KEY_KPCOMMA, 121)		\
	code(KEY_HANGUEL, 122)		\
	code(KEY_HANJA, 123)		\
	code(KEY_YEN, 124)			\
	code(KEY_LEFTMETA, 125)		\
	code(KEY_RIGHTMETA, 126)	\
	code(KEY_COMPOSE, 127)		\
	code(KEY_STOP, 128)			\
	code(KEY_AGAIN, 129)		\
	code(KEY_PROPS, 130)		\
	code(KEY_UNDO, 131)			\
	code(KEY_FRONT, 132)		\
	code(KEY_COPY, 133)			\
	code(KEY_OPEN, 134)			\
	code(KEY_PASTE, 135)		\
	code(KEY_FIND, 136)			\
	code(KEY_CUT, 137)			\
	code(KEY_HELP, 138)			\
	code(KEY_MENU, 139)			\
	code(KEY_CALC, 140)			\
	code(KEY_SETUP, 141)		\
	code(KEY_SLEEP, 142)		\
	code(KEY_WAKEUP, 143)		\
	code(KEY_FILE, 144)			\
	code(KEY_SENDFILE, 145)		\
	code(KEY_DELETEFILE, 146)	\
	code(KEY_XFER, 147)			\
	code(KEY_PROG1, 148)		\
	code(KEY_PROG2, 149)		\
	code(KEY_WWW, 150)			\
	code(KEY_MSDOS, 151)		\
	code(KEY_COFFEE, 152)		\
	code(KEY_DIRECTION, 153)	\
	code(KEY_CYCLEWINDOWS, 154)	\
	code(KEY_MAIL, 155)			\
	code(KEY_BOOKMARKS, 156)	\
	code(KEY_COMPUTER, 157)		\
	code(KEY_BACK, 158)			\
	code(KEY_FORWARD, 159)		\
	code(KEY_CLOSECD, 160)		\
	code(KEY_EJECTCD, 161)		\
	code(KEY_EJECTCLOSECD, 162)	\
	code(KEY_NEXTSONG, 163)		\
	code(KEY_PLAYPAUSE, 164)	\
	code(KEY_PREVIOUSSONG, 165)	\
	code(KEY_STOPCD, 166)		\
	code(KEY_RECORD, 167)		\
	code(KEY_REWIND, 168)		\
	code(KEY_PHONE, 169)		\
	code(KEY_ISO, 170)			\
	code(KEY_CONFIG, 171)		\
	code(KEY_HOMEPAGE, 172)		\
	code(KEY_REFRESH, 173)		\
	code(KEY_EXIT, 174)			\
	code(KEY_MOVE, 175)			\
	code(KEY_EDIT, 176)			\
	code(KEY_SCROLLUP, 177)		\
	code(KEY_SCROLLDOWN, 178)	\
	code(KEY_KPLEFTPAREN, 179)	\
	code(KEY_KPRIGHTPAREN, 180)	\
	code(KEY_F13, 183)			\
	code(KEY_F14, 184)			\
	code(KEY_F15, 185)			\
	code(KEY_F16, 186)			\
	code(KEY_F17, 187)			\
	code(KEY_F18, 188)			\
	code(KEY_F19, 189)			\
	code(KEY_F20, 190)			\
	code(KEY_F21, 191)			\
	code(KEY_F22, 192)			\
	code(KEY_F23, 193)			\
	code(KEY_F24, 194)			\
	code(KEY_PLAYCD, 200)		\
	code(KEY_PAUSECD, 201)		\
	code(KEY_PROG3, 202)		\
	code(KEY_PROG4, 203)		\
	code(KEY_SUSPEND, 205)		\
	code(KEY_CLOSE, 206)		\
	code(KEY_PLAY, 207)			\
	code(KEY_FASTFORWARD, 208)	\
	code(KEY_BASSBOOST, 209)	\
	code(KEY_PRINT, 210)		\
	code(KEY_HP, 211)			\
	code(KEY_CAMERA, 212)		\
	code(KEY_SOUND, 213)		\
	code(KEY_QUESTION, 214)		\
	code(KEY_EMAIL, 215)		\
	code(KEY_CHAT, 216)			\
	code(KEY_SEARCH, 217)		\
	code(KEY_CONNECT, 218)		\
	code(KEY_FINANCE, 219)		\
	code(KEY_SPORT, 220)		\
	code(KEY_SHOP, 221)			\
	code(KEY_ALTERASE, 222)		\
	code(KEY_CANCEL, 223)		\
	code(KEY_BRIGHTNESSDOWN, 224)\
	code(KEY_BRIGHTNESSUP, 225)	\
	code(KEY_MEDIA, 226)		\
	code(KEY_SWITCHVIDEOMODE, 227)\
	code(KEY_KBDILLUMTOGGLE, 228)\
	code(KEY_KBDILLUMDOWN, 229)	\
	code(KEY_KBDILLUMUP, 230)	\
	code(KEY_SEND, 231)			\
	code(KEY_REPLY, 232)		\
	code(KEY_FORWARDMAIL, 233)	\
	code(KEY_SAVE, 234)			\
	code(KEY_DOCUMENTS, 235)	\
	code(KEY_BATTERY, 236)
	//code(KEY_UNKNOWN, 240)

#define DEFINE_ENUM_TYPE(type, value) type = value,
enum KeyCode {
	KEYCODE_LIST(DEFINE_ENUM_TYPE)
};
#undef DEFINE_ENUM_TYPE

KeyCode getKeyCode(string strText);
string typeString(KeyCode code);

#endif