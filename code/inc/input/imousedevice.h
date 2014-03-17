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

#ifndef __IMOUSE_DEVICE_H__
#define __IMOUSE_DEVICE_H__

namespace rengine3d {

	class IMouseDevice: public IInputDevice {
	public:
		IMouseDevice(){};
		virtual ~IMouseDevice(){};

		virtual void Reset(void) = 0;
		virtual void Update(void) = 0;

		virtual void SetCursorPos(int x, int y) = 0;

		virtual void SetSensitivity(real value) = 0;
		virtual real GetSensitivity(void) const = 0;

		virtual CVec2 GetAbsPosition(void) = 0;
		virtual CVec2 GetRelPosition(void) = 0;

		virtual bool ButtonIsDown(mouseButton_t button) = 0;
	};
}

#endif
