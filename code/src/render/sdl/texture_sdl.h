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

#ifndef __TEXTURESDL_H__
#define __TEXTURESDL_H__

namespace rengine3d {

	class CTextureSDL: public ITexture {
	public:
		static IResource *FactoryFunc( const string_t& name) { return new CTextureSDL( name); }

		CTextureSDL(const string_t& name);
		virtual ~CTextureSDL();

		virtual bool CreateFromArray(unsigned char* data, uint width, uint height, uint depth, uint bpp);

		virtual bool Load(const char* data, uint size);
		virtual void UnLoad(void);
	private:
		uint InitCreation(int id);
		void PostCreation(uint target);
		bool LoadSTBI(const char* data, uint size);
	private:

	};

}

#endif
