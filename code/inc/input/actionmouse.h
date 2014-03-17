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

#ifndef __ACTIONMOUSE_H__
#define __ACTIONMOUSE_H__

namespace rengine3d {

	class CActionMouse: public IInputAction {
	public:
		CActionMouse(const char* name, IInputSystem* inputSystem, mouseButton_t button);
		virtual ~CActionMouse();

		virtual void Update(real timeStep);

		virtual bool IsPressed(void);
		virtual bool IsDown(void);

		mouseButton_t GetButton(void) { return m_button; }

		virtual string_t GetInputName(void);
		virtual string_t GetInputType(void);
	private:
		mouseButton_t m_button;
		IInputSystem* m_inputSystem;
	};

	r_inline CActionMouse::CActionMouse(const char* name, IInputSystem* inputSystem, mouseButton_t button): IInputAction(name) {
		m_inputSystem	= inputSystem;
		m_button		= button;
	}

	r_inline CActionMouse::~CActionMouse() {
	}

	r_inline void CActionMouse::Update(real timeStep) {
	}

	r_inline bool CActionMouse::IsPressed(void) {
		return m_inputSystem->GetMouseDevice()->ButtonIsDown(m_button);
	}

	r_inline bool CActionMouse::IsDown(void) {
		return m_inputSystem->GetMouseDevice()->ButtonIsDown(m_button);
	}


	r_inline string_t CActionMouse::GetInputName(void) {
		switch(m_button)
		{
		case mouseButton_Left:		return "LeftMouse";
		case mouseButton_Middle:	return "MiddleMouse";
		case mouseButton_Right:		return "RightMouse";
		case mouseButton_WheelUp:	return "WheelUp";
		case mouseButton_WheelDown:	return "WheelDown";
		}

		return "Unknown";
	}

	r_inline string_t CActionMouse::GetInputType(void) {
		return "CActionMouse";
	}

}

#endif
