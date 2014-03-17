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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "keyboard_sdl.h"
#include "inputsystem_sdl.h"

namespace rengine3d {

	CKeyboardSDL::CKeyboardSDL(CInputSystemSDL* inputSys) {
		m_inputSys = inputSys;

		m_keyArray.resize(key_Count);
		m_keyArray.assign(m_keyArray.size(),false);
	}

	CKeyboardSDL::~CKeyboardSDL() {
		this->Shutdown();
	}

	bool CKeyboardSDL::Init(void) {
		Log("\tInitializing SDL keyboard device...\n");
		m_initialized = true;
		return m_initialized;
	}

	void CKeyboardSDL::Shutdown(void) {
		Log("\tShutdown SDL keyboard device...\n");
		m_initialized = false;
	}

	inputDeviceType_t CKeyboardSDL::GetType(void) {
		return inputDeviceType_Keyboard;
	}

	string_t CKeyboardSDL::GetName(void) {
		return "CKeyboardSDL";
	}

	void CKeyboardSDL::Update(void) {
 		sdlEventVector_t events = m_inputSys->GetEvents();

		m_keysPressed.clear();
		m_keyArray.assign(m_keyArray.size(),false);

		sdlEventVector_t::iterator it = events.begin();

		for(; it != events.end(); ++it) {
			SDL_Event* event = &(*it);

			if(event->type != SDL_KEYDOWN && event->type != SDL_KEYUP) {
				continue;
			}

			keyboardKey_t key = SDLToKey(event->key.keysym.sym);

			m_keyArray[key] = event->type == SDL_KEYDOWN?true:false;

			if(event->type == SDL_KEYDOWN) {
				int sdl_mod = event->key.keysym.mod;
				m_modifiers = keyModifier_None;

				if(sdl_mod & KMOD_CTRL)		
					m_modifiers |= keyModifier_Ctrl;

				if(sdl_mod & KMOD_SHIFT)	
					m_modifiers |= keyModifier_Shift;

				if(sdl_mod & KMOD_ALT)		
					m_modifiers |= keyModifier_Alt;

				m_keysPressed.push_back(keyPress_t(key, event->key.keysym.scancode, m_modifiers));
			}
		}
	}

	keyboardKey_t CKeyboardSDL::SDLToKey(int key) {
		switch(key)
		{
			case	SDLK_BACKSPACE: return key_BACKSPACE;
			case	SDLK_TAB:return  key_TAB;
			case 	SDLK_CLEAR: return key_CLEAR;
			case 	SDLK_RETURN: return key_RETURN;
			case 	SDLK_PAUSE: return key_PAUSE;
			case 	SDLK_ESCAPE: return key_ESCAPE;
			case 	SDLK_SPACE: return key_SPACE;
			case 	SDLK_EXCLAIM: return key_EXCLAIM;
			case 	SDLK_QUOTEDBL: return key_QUOTEDBL;
			case 	SDLK_HASH: return key_HASH;
			case 	SDLK_DOLLAR: return key_DOLLAR;
			case 	SDLK_AMPERSAND: return key_AMPERSAND;
			case 	SDLK_QUOTE: return key_QUOTE;
			case 	SDLK_LEFTPAREN: return key_LEFTPAREN;
			case 	SDLK_RIGHTPAREN: return key_RIGHTPAREN;
			case 	SDLK_ASTERISK: return key_ASTERISK;
			case 	SDLK_PLUS: return key_PLUS;
			case 	SDLK_COMMA: return key_COMMA;
			case 	SDLK_MINUS: return key_MINUS;
			case 	SDLK_PERIOD: return key_PERIOD;
			case 	SDLK_SLASH: return key_SLASH;
			case 	SDLK_0: return key_0;
			case 	SDLK_1: return key_1;
			case 	SDLK_2: return key_2;
			case 	SDLK_3: return key_3;
			case 	SDLK_4: return key_4;
			case 	SDLK_5: return key_5;
			case 	SDLK_6: return key_6;
			case 	SDLK_7: return key_7;
			case 	SDLK_8: return key_8;
			case 	SDLK_9: return key_9;
			case 	SDLK_COLON: return key_COLON;
			case 	SDLK_SEMICOLON: return key_SEMICOLON;
			case 	SDLK_LESS: return key_LESS;
			case 	SDLK_EQUALS: return key_EQUALS;
			case 	SDLK_GREATER: return key_GREATER;
			case 	SDLK_QUESTION: return key_QUESTION;
			case 	SDLK_AT: return key_AT;
			case 	SDLK_LEFTBRACKET: return key_LEFTBRACKET;
			case 	SDLK_BACKSLASH: return key_BACKSLASH;
			case 	SDLK_RIGHTBRACKET: return key_RIGHTBRACKET;
			case 	SDLK_CARET: return key_CARET;
			case 	SDLK_UNDERSCORE: return key_UNDERSCORE;
			case 	SDLK_BACKQUOTE: return key_BACKQUOTE;
			case 	SDLK_a: return key_a;
			case 	SDLK_b: return key_b;
			case 	SDLK_c: return key_c;
			case 	SDLK_d: return key_d;
			case 	SDLK_e: return key_e;
			case 	SDLK_f: return key_f;
			case 	SDLK_g: return key_g;
			case 	SDLK_h: return key_h;
			case 	SDLK_i: return key_i;
			case 	SDLK_j: return key_j;
			case 	SDLK_k: return key_k;
			case 	SDLK_l: return key_l;
			case 	SDLK_m: return key_m;
			case 	SDLK_n: return key_n;
			case 	SDLK_o: return key_o;
			case 	SDLK_p: return key_p;
			case 	SDLK_q: return key_q;
			case 	SDLK_r: return key_r;
			case 	SDLK_s: return key_s;
			case 	SDLK_t: return key_t;
			case 	SDLK_u: return key_u;
			case 	SDLK_v: return key_v;
			case 	SDLK_w: return key_w;
			case 	SDLK_x: return key_x;
			case 	SDLK_y: return key_y;
			case 	SDLK_z: return key_z;
			case 	SDLK_DELETE: return key_DELETE;
			//case 	SDLK_KP0: return key_KP0;
			//case 	SDLK_KP1: return key_KP1;
			//case 	SDLK_KP2: return key_KP2;
			//case 	SDLK_KP3: return key_KP3;
			//case 	SDLK_KP4: return key_KP4;
			//case 	SDLK_KP5: return key_KP5;
			//case 	SDLK_KP6: return key_KP6;
			//case 	SDLK_KP7: return key_KP7;
			//case 	SDLK_KP8: return key_KP8;
			//case 	SDLK_KP9: return key_KP9;
			case 	SDLK_KP_PERIOD: return key_KP_PERIOD;
			case 	SDLK_KP_DIVIDE: return key_KP_DIVIDE;
			case 	SDLK_KP_MULTIPLY: return key_KP_MULTIPLY;
			case 	SDLK_KP_MINUS: return key_KP_MINUS;
			case 	SDLK_KP_PLUS: return key_KP_PLUS;
			case 	SDLK_KP_ENTER: return key_KP_ENTER;
			case 	SDLK_KP_EQUALS: return key_KP_EQUALS;
			case 	SDLK_UP: return key_UP;
			case 	SDLK_DOWN: return key_DOWN;
			case 	SDLK_RIGHT: return key_RIGHT;
			case 	SDLK_LEFT: return key_LEFT;
			case 	SDLK_INSERT: return key_INSERT;
			case 	SDLK_HOME: return key_HOME;
			case 	SDLK_END: return key_END;
			case 	SDLK_PAGEUP: return key_PAGEUP;
			case 	SDLK_PAGEDOWN: return key_PAGEDOWN;
			case 	SDLK_F1: return key_F1;
			case 	SDLK_F2: return key_F2;
			case 	SDLK_F3: return key_F3;
			case 	SDLK_F4: return key_F4;
			case 	SDLK_F5: return key_F5;
			case 	SDLK_F6: return key_F6;
			case 	SDLK_F7: return key_F7;
			case 	SDLK_F8: return key_F8;
			case 	SDLK_F9: return key_F9;
			case 	SDLK_F10: return key_F10;
			case 	SDLK_F11: return key_F11;
			case 	SDLK_F12: return key_F12;
			case 	SDLK_F13: return key_F13;
			case 	SDLK_F14: return key_F14;
			case 	SDLK_F15: return key_F15;
			case 	SDLK_NUMLOCKCLEAR: return key_NUMLOCK;
			case 	SDLK_CAPSLOCK: return key_CAPSLOCK;
			case 	SDLK_SCROLLLOCK: return key_SCROLLOCK;
			case 	SDLK_RSHIFT: return key_RSHIFT;
			case 	SDLK_LSHIFT: return key_LSHIFT;
			case 	SDLK_RCTRL: return key_RCTRL;
			case 	SDLK_LCTRL: return key_LCTRL;
			case 	SDLK_RALT: return key_RALT;
			case 	SDLK_LALT: return key_LALT;
			//case 	SDLK_RMETA: return key_RMETA;
			//case 	SDLK_LMETA: return key_LMETA;
			//case 	SDLK_LSUPER: return key_LSUPER;
			//case 	SDLK_RSUPER: return key_RSUPER;
			case 	SDLK_MODE: return key_MODE;
			case 	SDLK_HELP: return key_HELP;
			case 	SDLK_PRINTSCREEN: return key_PRINT;
			case 	SDLK_SYSREQ: return key_SYSREQ;
			//case 	SDLK_BREAK: return key_BREAK;
			case 	SDLK_MENU: return key_MENU;
			case 	SDLK_POWER: return key_POWER;
			//case 	SDLK_EURO: return key_EURO;
		}

		return key_NONE;
	}

	bool CKeyboardSDL::KeyIsDown(keyboardKey_t key) {
		return m_keyArray[key];
	}

	bool CKeyboardSDL::KeyPressed() {
		return m_keysPressed.empty()==false;
	}

	keyPress_t CKeyboardSDL::GetKey(void) {
		keyPress_t key = m_keysPressed.front();
		m_keysPressed.pop_front();
		return key;
	}

	uint CKeyboardSDL::GetModifiers(void) {
		return m_modifiers;
	}

	string_t CKeyboardSDL::KeyToString(keyboardKey_t key) {
		return "";
	}

	keyboardKey_t CKeyboardSDL::StringToKey(string_t str) {
		return key_NONE;
	}

}
