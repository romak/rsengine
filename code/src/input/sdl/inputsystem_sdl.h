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

#ifndef __CINPUTSYSTEM_SDL_H__
#define __CINPUTSYSTEM_SDL_H__

#include "sdl/SDL_config.h"
#include "sdl/SDL.h"

namespace rengine3d {

	class CKeyboardSDL;

	typedef std::vector<SDL_Event>		sdlEventVector_t;

	class CInputSystemSDL: public IInputSystem {
	public:
		CInputSystemSDL();
		virtual ~CInputSystemSDL();

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		virtual bool Init();
		virtual void Shutdown(void) ;

		virtual void Update(real timeStep);
		virtual void EndUpdate(void);

		virtual void ProcessEvent(void* _event);

		virtual void AddAction(IInputAction* action);
		virtual IInputAction* GetAction(string_t name);
		virtual bool RemoveAction(string_t name);

		virtual bool CheckAction(const string_t name);

		virtual IKeyboardDevice* GetKeyboardDevice(void);
		virtual IMouseDevice* GetMouseDevice(void);

		sdlEventVector_t GetEvents(void);
	private:
		sdlEventVector_t	m_events;
		CKeyboardSDL*		m_keyboard;
	};

}

#endif
