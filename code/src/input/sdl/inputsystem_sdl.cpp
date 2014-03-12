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
#include "sdl/SDL_config.h"
#include "sdl/SDL.h"
#include "inputsystem_sdl.h"

namespace rengine3d {

	CInputSystemSDL::CInputSystemSDL() {

	}

	CInputSystemSDL::~CInputSystemSDL() {
		this->Shutdown();
	}

	bool CInputSystemSDL::Init() {
		Log("\tInitializing SDL input system...\n");
		return true;
	}

	void CInputSystemSDL::Shutdown(void) {
		Log("\tShutdown SDL input system...\n");
	}

	void CInputSystemSDL::Update(real timeStep) {
	}

	void CInputSystemSDL::ProcessEvent(void* _event) {
	}

	string_t CInputSystemSDL::GetName(void) {
		return "CInputSystemSDL";
	}

	string_t CInputSystemSDL::GetDescription(void) {
		return "CInputSystemSDL";
	}

	string_t CInputSystemSDL::GetVersion(void) {
		return "0.0.1";
	}

	void CInputSystemSDL::AddAction(IInputAction* action) {

	}

	IInputAction* CInputSystemSDL::GetAction(string_t name) {
		return NULL;
	}

	bool CInputSystemSDL::RemoveAction(string_t name) {
		return true;
	}

	bool CInputSystemSDL::CheckAction(const string_t name) {
		return true;
	}

	IKeyboardDevice* CInputSystemSDL::GetKeyboardDevice(void) {
		return NULL;
	}

	IMouseDevice* CInputSystemSDL::GetMouseDevice(void) {
		return NULL;
	}

}