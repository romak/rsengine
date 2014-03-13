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
#include "inputsystem_sdl.h"
#include "keyboard_sdl.h"
#include "mouse_sdl.h"

namespace rengine3d {

	CInputSystemSDL::CInputSystemSDL(IRenderDriver* renderDriver):m_renderDriver(renderDriver) {
		m_keyboard = new CKeyboardSDL(this);
		m_mouse = new CMouseSDL(this, renderDriver);

		m_events.clear();
	}

	CInputSystemSDL::~CInputSystemSDL() {
		SafeDelete(m_keyboard);
		SafeDelete(m_mouse);
		this->Shutdown();
	}

	bool CInputSystemSDL::Init() {
		Log("\tInitializing SDL input system...\n");

		if (!m_keyboard->Init()) {
			return false;
		}

		return true;
	}

	void CInputSystemSDL::Shutdown(void) {
		Log("\tShutdown SDL input system...\n");

		for ( actionMapIt_t  it = m_actionsMap.begin(); it != m_actionsMap.end(); ++it ) {
			SafeDelete(it->second);
		}

		m_actionsMap.clear();
	}

	void CInputSystemSDL::Update(real timeStep) {

		m_keyboard->Update();
		m_mouse->Update();

	}

	void CInputSystemSDL::EndUpdate(void) {
		m_events.clear();
	}

	void CInputSystemSDL::ProcessEvent(void* _event) {
		SDL_Event* Event = (SDL_Event*)_event;
		m_events.push_back(*Event);
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
		m_actionsMap.insert(actionMap_t::value_type(action->GetName(), action));	
	}

	IInputAction* CInputSystemSDL::GetAction(string_t name) {
		actionMapIt_t it = m_actionsMap.find(name);
		if (it==m_actionsMap.end())
			return NULL;
		return it->second;
	}

	bool CInputSystemSDL::RemoveAction(string_t name) {
		actionMapIt_t it = m_actionsMap.find(name);
		if (it==m_actionsMap.end())
			return false;

		IInputAction* action = it->second;
		SafeDelete(action);
		m_actionsMap.erase(name);

		return true;
	}

	bool CInputSystemSDL::CheckAction(const string_t name) {
		IInputAction* action = GetAction(name);
		if (!action)
			return false;
		return action->IsPressed();
	}

	IKeyboardDevice* CInputSystemSDL::GetKeyboardDevice(void) {
		return m_keyboard;
	}

	IMouseDevice* CInputSystemSDL::GetMouseDevice(void) {
		return m_mouse;
	}

	sdlEventVector_t CInputSystemSDL::GetEvents(void) {
		return m_events;
	}

}