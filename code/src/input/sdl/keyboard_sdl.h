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

#ifndef __CKEYBOARD_SDL_H__
#define __CKEYBOARD_SDL_H__

namespace rengine3d {

	class CInputSystemSDL;

	class CKeyboardSDL: public IKeyboardDevice {
	public:
		CKeyboardSDL(CInputSystemSDL* inputSys);
		virtual ~CKeyboardSDL();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual inputDeviceType_t GetType(void);
		virtual string_t GetName(void);

		virtual void Update(void);

		virtual bool KeyIsDown(keyboardKey_t key);
		virtual bool KeyPressed();
		virtual keyPress_t GetKey(void);

		virtual uint GetModifiers(void);

		virtual string_t KeyToString(keyboardKey_t key);
		virtual keyboardKey_t StringToKey(string_t str);
	private:
		std::vector<bool>		m_keyArray; 
		std::list<keyPress_t>	m_keysPressed;
		CInputSystemSDL*		m_inputSys;
	};
}

#endif
