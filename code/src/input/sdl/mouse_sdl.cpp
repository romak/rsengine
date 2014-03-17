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
#include "mouse_sdl.h"
#include "inputsystem_sdl.h"

namespace rengine3d {

	CMouseSDL::CMouseSDL(CInputSystemSDL* inputSys, IRenderDriver* renderDriver):m_inputSys(inputSys), m_renderDriver(renderDriver) {
		m_buttonArray.resize(mouseButton_Count);
		m_buttonArray.assign(m_buttonArray.size(),false);
	}

	CMouseSDL::~CMouseSDL() {
		this->Shutdown();
	}

	bool CMouseSDL::Init(void) {
		Log("\tInitializing SDL mouse device...\n");
		m_initialized = true;
		return m_initialized;
	}

	void CMouseSDL::Shutdown(void) {
		Log("\tShutdown SDL mouse device...\n");
		m_initialized = false;
	}

	inputDeviceType_t CMouseSDL::GetType(void) {
		return inputDeviceType_Mouse;
	}

	string_t CMouseSDL::GetName(void) {
		return "CMouseSDL";
	}

	void CMouseSDL::Reset(void) {
	}

	void CMouseSDL::Update(void) {

		CVec2 screenSize	= m_renderDriver->GetScreenSize();
		CVec2 virtualSize	= m_renderDriver->GetVirtualSize();

		m_wheelUpMoved		= false;
		m_wheelDownMoved	= false;

		sdlEventVector_t events = m_inputSys->GetEvents();
		sdlEventVector_t::iterator it = events.begin();

		for(; it != events.end(); ++it) {
			SDL_Event* event = &(*it);

			if(	event->type != SDL_MOUSEMOTION && event->type != SDL_MOUSEBUTTONDOWN &&	event->type != SDL_MOUSEBUTTONUP){
				continue;
			}

			if(event->type == SDL_MOUSEMOTION) {
				m_absPos = CVec2((float)event->motion.x,(float)event->motion.y);
				m_absPos = (m_absPos/screenSize)*virtualSize;

				Uint8 buttonState = event->motion.state;

			}else {
				bool buttonIsDown = event->type==SDL_MOUSEBUTTONDOWN;

				switch(event->button.button)
				{
				case SDL_BUTTON_LEFT: 
					m_buttonArray[mouseButton_Left] = buttonIsDown;
					break;
				case SDL_BUTTON_MIDDLE: 
					m_buttonArray[mouseButton_Middle] = buttonIsDown;
					break;
				case SDL_BUTTON_RIGHT: 
					m_buttonArray[mouseButton_Right] = buttonIsDown;
					break;
					//case SDL_BUTTON_WHEELUP: 
					//	m_buttonArray[mouseButton_WheelUp] = buttonIsDown;
					//	if(buttonIsDown) m_wheelUpMoved = true;
					//	break;
					//case SDL_BUTTON_WHEELDOWN: 
					//	m_buttonArray[mouseButton_WheelDown] = buttonIsDown;
					//	if(buttonIsDown) m_wheelDownMoved = true;
					//	break;
				}
			}
		}

		int x,y; 

		SDL_GetRelativeMouseState(&x, &y);
		m_relPos = CVec2((float)x,(float)y);
		m_relPos = (m_relPos/screenSize)*virtualSize;
	}

	void CMouseSDL::SetCursorPos(int x, int y) {
	}

	void CMouseSDL::SetSensitivity(real value) {
	}

	real CMouseSDL::GetSensitivity(void) const {
		return 0;
	}

	CVec2 CMouseSDL::GetAbsPosition(void) {
		return m_absPos;
	}

	CVec2 CMouseSDL::GetRelPosition(void) {
		return m_relPos;
	}

	bool CMouseSDL::ButtonIsDown(mouseButton_t button) {
		return m_buttonArray[button];
	}


}


