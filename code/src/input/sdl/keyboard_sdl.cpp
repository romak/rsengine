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
		return true;
	}

	void CKeyboardSDL::Shutdown(void) {
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

		sdlEventVector_t::iterator it = events.begin();

		for(; it != events.end(); ++it) {
			SDL_Event* event = &(*it);
		}


	}

	bool CKeyboardSDL::KeyIsDown(keyboardKey_t key) {
		return false;
	}

	bool CKeyboardSDL::KeyPressed() {
		return false;
	}

	keyPress_t CKeyboardSDL::GetKey(void) {
		keyPress_t keyPress;
		return keyPress;
	}

	uint CKeyboardSDL::GetModifiers(void) {
		return 0;
	}

	string_t CKeyboardSDL::KeyToString(keyboardKey_t key) {
		return "";
	}

	keyboardKey_t CKeyboardSDL::StringToKey(string_t str) {
		return key_NONE;
	}

}
