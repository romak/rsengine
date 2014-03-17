/*
* Copyright (C) 2009-2014 - Roman Kalynchuk
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

#ifndef __ACTIONKEYBOARD_H__
#define __ACTIONKEYBOARD_H__

namespace rengine3d {

	class CActionKeyboard: public IInputAction {
	public:
		CActionKeyboard(const char* name, IInputSystem* inputSystem, keyboardKey_t key);
		virtual ~CActionKeyboard();

		virtual void Update(real timeStep);

		virtual bool IsPressed(void);
		virtual bool IsDown(void);

		keyboardKey_t GetKey(void) { return m_key; }

		virtual string_t GetInputName(void);
		virtual string_t GetInputType(void);
	private:
		keyboardKey_t m_key;
		IInputSystem* m_inputSystem;
	};

	r_inline CActionKeyboard::CActionKeyboard(const char* name, IInputSystem* inputSystem, keyboardKey_t key): IInputAction(name) {
		m_inputSystem	= inputSystem;
		m_key			= key;
	}

	r_inline CActionKeyboard::~CActionKeyboard() {
	}

	r_inline void CActionKeyboard::Update(real timeStep) {
	}

	r_inline bool CActionKeyboard::IsPressed(void) {
		if (m_inputSystem->GetKeyboardDevice()->KeyPressed()) {
			return m_inputSystem->GetKeyboardDevice()->KeyIsDown(m_key);
		}

		return false;
	}

	r_inline bool CActionKeyboard::IsDown(void) {
		return m_inputSystem->GetKeyboardDevice()->KeyIsDown(m_key);
	}

	r_inline string_t CActionKeyboard::GetInputName(void) {
		string_t strKey;

		switch(m_key)
		{
		case key_BACKSPACE: strKey.append("BackSpace"); break;
		case key_TAB: strKey.append("Tab"); break;
		case key_CLEAR: strKey.append("Clear"); break;
		case key_RETURN: strKey.append("Return"); break;
		case key_PAUSE: strKey.append("Pause"); break;
		case key_ESCAPE: strKey.append("Escape"); break;
		case key_SPACE: strKey.append("Space"); break;
		case key_EXCLAIM: strKey.append("Exclaim"); break;
		case key_QUOTEDBL: strKey.append("DblQoute"); break;
		case key_HASH: strKey.append("Hash"); break;
		case key_DOLLAR: strKey.append("Dollar"); break;
		case key_AMPERSAND: strKey.append("Ampersand"); break;
		case key_QUOTE: strKey.append("Quote"); break;
		case key_LEFTPAREN: strKey.append("LeftParent"); break;
		case key_RIGHTPAREN: strKey.append("RightParent"); break;
		case key_ASTERISK: strKey.append("Asterisk"); break;
		case key_PLUS: strKey.append("Plus"); break;
		case key_COMMA: strKey.append("Comma"); break;
		case key_MINUS: strKey.append("Minus"); break;
		case key_PERIOD: strKey.append("Period"); break;
		case key_SLASH: strKey.append("Slash"); break;
		case key_0: strKey.append("0"); break;
		case key_1: strKey.append("1"); break;
		case key_2: strKey.append("2"); break;
		case key_3: strKey.append("3"); break;
		case key_4: strKey.append("4"); break;
		case key_5: strKey.append("5"); break;
		case key_6: strKey.append("6"); break;
		case key_7: strKey.append("7"); break;
		case key_8: strKey.append("8"); break;
		case key_9: strKey.append("9"); break;
		case key_COLON: strKey.append("Colon"); break;
		case key_SEMICOLON: strKey.append("SemiColon"); break;
		case key_LESS: strKey.append("Less"); break;
		case key_EQUALS: strKey.append("Equals"); break;
		case key_GREATER: strKey.append("Greater"); break;
		case key_QUESTION: strKey.append("Question"); break;
		case key_AT: strKey.append("At"); break;
		case key_LEFTBRACKET: strKey.append("LeftBracket"); break;
		case key_BACKSLASH: strKey.append("BackSlash"); break;
		case key_RIGHTBRACKET: strKey.append("RightBracket"); break;
		case key_CARET: strKey.append("Caret"); break;
		case key_UNDERSCORE: strKey.append("Underscore"); break;
		case key_BACKQUOTE: strKey.append("BackQuote"); break;
		case key_a: strKey.append("A"); break;
		case key_b: strKey.append("B"); break;
		case key_c: strKey.append("C"); break;
		case key_d: strKey.append("D"); break;
		case key_e: strKey.append("E"); break;
		case key_f: strKey.append("F"); break;
		case key_g: strKey.append("G"); break;
		case key_h: strKey.append("H"); break;
		case key_i: strKey.append("I"); break;
		case key_j: strKey.append("J"); break;
		case key_k: strKey.append("K"); break;
		case key_l: strKey.append("L"); break;
		case key_m: strKey.append("M"); break;
		case key_n: strKey.append("N"); break;
		case key_o: strKey.append("O"); break;
		case key_p: strKey.append("P"); break;
		case key_q: strKey.append("Q"); break;
		case key_r: strKey.append("R"); break;
		case key_s: strKey.append("S"); break;
		case key_t: strKey.append("T"); break;
		case key_u: strKey.append("U"); break;
		case key_v: strKey.append("V"); break;
		case key_w: strKey.append("W"); break;
		case key_x: strKey.append("X"); break;
		case key_y: strKey.append("Y"); break;
		case key_z: strKey.append("Z"); break;
		case key_DELETE: strKey.append("Delete"); break;
		case key_KP0: strKey.append("Kp0"); break;
		case key_KP1: strKey.append("Kp1"); break;
		case key_KP2: strKey.append("Kp2"); break;
		case key_KP3: strKey.append("Kp3"); break;
		case key_KP4: strKey.append("Kp4"); break;
		case key_KP5: strKey.append("Kp5"); break;
		case key_KP6: strKey.append("Kp6"); break;
		case key_KP7: strKey.append("Kp7"); break;
		case key_KP8: strKey.append("Kp8"); break;
		case key_KP9: strKey.append("Kp9"); break;
		case key_KP_PERIOD: strKey.append("Period"); break;
		case key_KP_DIVIDE: strKey.append("Divide"); break;
		case key_KP_MULTIPLY: strKey.append("Multiply"); break;
		case key_KP_MINUS: strKey.append("Minus"); break;
		case key_KP_PLUS: strKey.append("Plus"); break;
		case key_KP_ENTER: strKey.append("Enter"); break;
		case key_KP_EQUALS: strKey.append("Equals"); break;
		case key_UP: strKey.append("Up"); break;
		case key_DOWN: strKey.append("Down"); break;
		case key_RIGHT: strKey.append("Right"); break;
		case key_LEFT: strKey.append("Left"); break;
		case key_INSERT: strKey.append("Insert"); break;
		case key_HOME: strKey.append("Home"); break;
		case key_END: strKey.append("End"); break;
		case key_PAGEUP: strKey.append("PageUp"); break;
		case key_PAGEDOWN: strKey.append("PageDown"); break;
		case key_F1: strKey.append("F1"); break;
		case key_F2: strKey.append("F2"); break;
		case key_F3: strKey.append("F3"); break;
		case key_F4: strKey.append("F4"); break;
		case key_F5: strKey.append("F5"); break;
		case key_F6: strKey.append("F6"); break;
		case key_F7: strKey.append("F7"); break;
		case key_F8: strKey.append("F8"); break;
		case key_F9: strKey.append("F9"); break;
		case key_F10: strKey.append("F10"); break;
		case key_F11: strKey.append("F11"); break;
		case key_F12: strKey.append("F12"); break;
		case key_F13: strKey.append("F13"); break;
		case key_F14: strKey.append("F14"); break;
		case key_F15: strKey.append("F15"); break;
		case key_NUMLOCK: strKey.append("NumLock"); break;
		case key_CAPSLOCK: strKey.append("CapsLock"); break;
		case key_SCROLLOCK: strKey.append("ScrollLock"); break;
		case key_RSHIFT: strKey.append("RightShift"); break;
		case key_LSHIFT: strKey.append("LeftShift"); break;
		case key_RCTRL: strKey.append("RightControl"); break;
		case key_LCTRL: strKey.append("LeftControl"); break;
		case key_RALT: strKey.append("RightAlt"); break;
		case key_LALT: strKey.append("LeftAlt"); break;
		case key_RMETA: strKey.append("RightMeta"); break;
		case key_LMETA: strKey.append("LeftMeta"); break;
		case key_LSUPER: strKey.append("LeftSuper"); break;
		case key_RSUPER: strKey.append("RightSuper"); break;
		case key_MODE: strKey.append("Mode"); break;
		case key_HELP: strKey.append("Help"); break;
		case key_PRINT: strKey.append("Print"); break;
		case key_SYSREQ: strKey.append("SysReq"); break;
		case key_BREAK: strKey.append("Break"); break;
		case key_MENU: strKey.append("Menu"); break;
		case key_POWER: strKey.append("Power"); break;
		case key_EURO: strKey.append("Euro"); break;
		case key_NONE: strKey.append("None"); break;
		}

		return "Unknown";
	}

	r_inline string_t CActionKeyboard::GetInputType(void) {
		return "CActionKeyboard";
	}

}

#endif
