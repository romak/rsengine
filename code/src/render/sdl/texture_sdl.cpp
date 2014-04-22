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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "texture_sdl.h"
#include "stb/stb_image.h"

namespace rengine3d {

	CTextureSDL::CTextureSDL(const string_t& name): ITexture(name) {
	}

	CTextureSDL::~CTextureSDL() {
		this->UnLoad();
	}

	bool CTextureSDL::LoadSTBI(const char* data, uint size) {
		bool hdr = false;
		if( stbi_is_hdr_from_memory( (unsigned char *)data, size ) > 0 ) hdr = true;

		int comps;
		void *pixels = NULL;
		if( hdr )
			pixels = stbi_loadf_from_memory( (unsigned char *)data, size, &m_width, &m_height, &comps, 4 );
		else
			pixels = stbi_load_from_memory( (unsigned char *)data, size, &m_width, &m_height, &comps, 4 );

		if( pixels == NULL )
			return false;

		// Swizzle RGBA -> BGRA
		uint *ptr = (uint *)pixels;
		for( uint i = 0, si = m_width * m_height; i < si; ++i ) {
			uint col = *ptr;
			*ptr++ = (col & 0xFF00FF00) | ((col & 0x000000FF) << 16) | ((col & 0x00FF0000) >> 16);
		}

		stbi_image_free(pixels);

		return true;
	}

	bool CTextureSDL::Load(const char* data, uint size) {
		if (m_loaded) {
			return false;
		}

		if (data == NULL || size == 0) {
			return false;
		}

		m_loaded = LoadSTBI(data, size);

		return m_loaded;
	}

	void CTextureSDL::UnLoad(void) {
		m_loaded = false;
	}

}