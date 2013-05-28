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

#ifndef __IKEYBOARD_DEVICE_H__
#define __IKEYBOARD_DEVICE_H__

namespace rengine3d {

	class IKeyboardDevice: public IInputDevice {
	public:
		IKeyboardDevice(){};
		virtual ~IKeyboardDevice(){};

		virtual void Update(void) = 0;

		virtual bool KeyIsDown(keyboardKey_t key) = 0;
		virtual bool KeyPressed() = 0;
		virtual keyPress_t GetKey(void) = 0;

		virtual void OnKeyPress(int key, int action) = 0;
		virtual void OnCharPress(int character, int action) = 0;

		virtual uint GetModifiers(void) = 0;

		virtual string_t KeyToString(keyboardKey_t key) = 0;
		virtual keyboardKey_t StringToKey(string_t str) = 0;
	};
}

#endif
