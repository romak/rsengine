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
#include "inputsystem.h"

namespace rengine3d {

	CInputSystem::CInputSystem() {

#ifdef  USE_SDL
#endif

	}

	CInputSystem::~CInputSystem() {
#ifdef  USE_SDL
#endif

	}

	bool CInputSystem::Init() {
		Log("\tInitializing input system...\n");
		return true;
	}

	void CInputSystem::Shutdown(void) {
		Log("\tShutdown input system...\n");
	}

	string_t CInputSystem::GetName(void) {
		return "CInputSystem";
	}

	string_t CInputSystem::GetDescription(void) {
		return "CInputSystem";
	}

	string_t CInputSystem::GetVersion(void) {
		return "0.0.1";
	}

	void CInputSystem::OnKeyDown(int sym, int mod, uint unicode) {
	}

    void CInputSystem::OnKeyUp(int sym, int mod, uint unicode) {
	}

	void CInputSystem::AddAction(IInputAction* action) {

	}

	IInputAction* CInputSystem::GetAction(string_t name) {
		return NULL;
	}

	bool CInputSystem::RemoveAction(string_t name) {
		return true;
	}

	bool CInputSystem::CheckAction(const string_t name) {
		return true;
	}

	IKeyboardDevice* CInputSystem::GetKeyboardDevice(void) {
		return NULL;
	}

	IMouseDevice* CInputSystem::GetMouseDevice(void) {
		return NULL;
	}

}
