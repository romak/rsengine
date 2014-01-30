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

#ifndef __CRENDERDRIVERSDL_H__
#define __CRENDERDRIVERSDL_H__

namespace rengine3d {

	class CRenderDriverSDL: public IRenderDriver {
	public:
		CRenderDriverSDL(IFileSystem* fs, IVarSystem* vs);
		virtual ~CRenderDriverSDL();

		virtual bool Init();
		virtual void Shutdown(void);

		virtual bool SetDisplayMode(uint w, uint h, uint bpp, uint multiSampling, bool fs);

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

	private:
		uint m_width;
		uint m_height;
		uint m_bpp;
		uint m_multiSampling;
		uint m_fs;

		SDL_Surface*	m_screen;
		SDL_Window*		m_window;

	};
}

#endif
