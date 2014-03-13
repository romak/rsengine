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

#ifndef __IRENDERDRIVER_H__
#define __IRENDERDRIVER_H__

namespace rengine3d {

	class IRenderDriver: public ISubSystem  {
	public:
		IRenderDriver(){};
		virtual ~IRenderDriver(){};

		virtual bool SetDisplayMode(uint w, uint h, uint bpp, uint multiSampling, bool fs) = 0;
		virtual void SetWindowCaption(const string_t& caption) = 0;

		virtual void ShowCursor(bool show) = 0;

		virtual CVec2 GetScreenSize(void)=0;
		virtual CVec2 GetVirtualSize(void)=0;

	};

}

#endif
