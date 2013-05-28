/*
* Copyright (C) 2009-2013 - Roman Kalynchuk
*
* This file is part of rsengine.
*
* REngine is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* REngine is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rsengine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __IINPUTTYPES_H__
#define __IINPUTTYPES_H__

namespace rengine3d {

	typedef enum {
		inputDeviceType_Mouse,
		inputDeviceType_Keyboard
	} inputDeviceType_t;

	typedef enum {
		mouseButton_Left,
		mouseButton_Right,
		mouseButton_Middle,
		mouseButton_WheelUp,
		mouseButton_WheelDown,
		mouseButton_Count
	} mouseButton_t;

	typedef enum {
		key_BACKSPACE,
		key_TAB,
		key_CLEAR,
		key_RETURN,
		key_PAUSE,
		key_ESCAPE,
		key_SPACE,
		key_EXCLAIM,
		key_QUOTEDBL,
		key_HASH,
		key_DOLLAR,
		key_AMPERSAND,
		key_QUOTE,
		key_LEFTPAREN,
		key_RIGHTPAREN,
		key_ASTERISK,
		key_PLUS,
		key_COMMA,
		key_MINUS,
		key_PERIOD,
		key_SLASH,
		key_0,
		key_1,
		key_2,
		key_3,
		key_4,
		key_5,
		key_6,
		key_7,
		key_8,
		key_9,
		key_COLON,
		key_SEMICOLON,
		key_LESS,
		key_EQUALS,
		key_GREATER,
		key_QUESTION,
		key_AT,
		key_LEFTBRACKET,
		key_BACKSLASH,
		key_RIGHTBRACKET,
		key_CARET,
		key_UNDERSCORE,
		key_BACKQUOTE,
		key_a,
		key_b,
		key_c,
		key_d,
		key_e,
		key_f,
		key_g,
		key_h,
		key_i,
		key_j,
		key_k,
		key_l,
		key_m,
		key_n,
		key_o,
		key_p,
		key_q,
		key_r,
		key_s,
		key_t,
		key_u,
		key_v,
		key_w,
		key_x,
		key_y,
		key_z,
		key_DELETE,
		key_KP0,
		key_KP1,
		key_KP2,
		key_KP3,
		key_KP4,
		key_KP5,
		key_KP6,
		key_KP7,
		key_KP8,
		key_KP9,
		key_KP_PERIOD,
		key_KP_DIVIDE,
		key_KP_MULTIPLY,
		key_KP_MINUS,
		key_KP_PLUS,
		key_KP_ENTER,
		key_KP_EQUALS,
		key_UP,
		key_DOWN,
		key_RIGHT,
		key_LEFT,
		key_INSERT,
		key_HOME,
		key_END,
		key_PAGEUP,
		key_PAGEDOWN,
		key_F1,
		key_F2,
		key_F3,
		key_F4,
		key_F5,
		key_F6,
		key_F7,
		key_F8,
		key_F9,
		key_F10,
		key_F11,
		key_F12,
		key_F13,
		key_F14,
		key_F15,
		key_NUMLOCK,
		key_CAPSLOCK,
		key_SCROLLOCK,
		key_RSHIFT,
		key_LSHIFT,
		key_RCTRL,
		key_LCTRL,
		key_RALT,
		key_LALT,
		key_RMETA,
		key_LMETA,
		key_LSUPER,
		key_RSUPER,
		key_MODE,
		key_HELP,
		key_PRINT,
		key_SYSREQ,
		key_BREAK,
		key_MENU,
		key_POWER,
		key_EURO,
		key_NONE,
		key_Count
	} keyboardKey_t;

	typedef enum {
		keyModifier_None	= 0x00000,
		keyModifier_Shift	= 0x00100,
		keyModifier_Ctrl	= 0x00200,
		keyModifier_Alt		= 0x00400,
		keyModifier_Count	= 5
	} keyModifier_t;

	typedef struct	{
		keyboardKey_t	key;
		int				modifier;
	}keyEvent_t;

	typedef struct	{
		mouseButton_t	button;
		int				modifier;
	}mouseEvent_t;

	struct keyPress_t {
		keyPress_t(){};
		keyPress_t(keyboardKey_t _key, int _unicode, int _modifier):key(_key), modifier(_modifier), unicode(_unicode) {};

		keyboardKey_t	key;
		int				modifier;
		int				unicode;
	} ;

}

#endif
