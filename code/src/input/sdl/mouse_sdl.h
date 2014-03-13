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

#ifndef __CMOUSE_SDL_H__
#define __CMOUSE_SDL_H__

namespace rengine3d {

	class CInputSystemSDL;

	class CMouseSDL: public IMouseDevice {
	public:
		CMouseSDL(CInputSystemSDL* inputSys, IRenderDriver* renderDriver);
		virtual ~CMouseSDL();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual inputDeviceType_t GetType(void);
		virtual string_t GetName(void);

		virtual void Reset(void);
		virtual void Update(void);

		virtual void SetCursorPos(int x, int y);

		virtual void SetSensitivity(real value);
		virtual real GetSensitivity(void) const;

		virtual CVec2 GetAbsPosition(void);
		virtual CVec2 GetRelPosition(void);

		virtual bool ButtonIsDown(mouseButton_t button);
	private:
		CInputSystemSDL*		m_inputSys;
		CVec2					m_absPos;
		CVec2					m_relPos;

		real					m_maxPercent;
		real					m_minPercent;
		int						m_bufferSize;
		bool					m_wheelUpMoved;
		bool					m_wheelDownMoved;

		std::vector<bool>		m_buttonArray;

		IRenderDriver*			m_renderDriver;

	};

}

#endif

