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

#ifndef __IINPUTSYSTEM_H__
#define __IINPUTSYSTEM_H__

namespace rengine3d {

	typedef std::map<string_t, IInputAction*>	actionMap_t;
	typedef actionMap_t::iterator				actionMapIt_t;

	class IInputSystem: public IUpdateable, public ISubSystem {
	public:
		IInputSystem(){};
		virtual ~IInputSystem(){};

		virtual void Update(real timeStep) = 0;
		virtual void EndUpdate(void) = 0;

		virtual void ProcessEvent(void* _event) = 0;

		virtual void AddAction(IInputAction* action) = 0;
		virtual IInputAction* GetAction(string_t name) = 0;
		virtual bool RemoveAction(string_t name) = 0;

		virtual bool CheckAction(const string_t name) = 0;

		virtual IKeyboardDevice* GetKeyboardDevice(void) = 0;
		virtual IMouseDevice* GetMouseDevice(void) = 0;
	};
}

#endif
