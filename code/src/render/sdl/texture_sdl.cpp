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
#include "glee/GLee.h"

namespace rengine3d {

	extern uint GetGLTextureTargetEnum(textureTarget_t target);

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

		CreateFromArray((uchar*)pixels, m_width, m_height, m_depth, m_bpp);

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
		glDeleteTextures(1,(GLuint *)&m_id);
		m_loaded = false;
	}

	uint CTextureSDL::InitCreation(int id) {
		GLenum GLTarget = GetGLTextureTargetEnum(m_target);

		glEnable(GLTarget);
		glBindTexture(GLTarget, id);

		return GLTarget;
	}

	void CTextureSDL::PostCreation(uint target) {
		if(m_useMipMaps && m_target != textureTarget_Rect) {
			if(m_filter == textureFilter_Bilinear)
				glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			else
				glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		} else {
			glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(target,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(target,GL_TEXTURE_WRAP_R,GL_REPEAT);

		glDisable(target);
	}

	bool CTextureSDL::CreateFromArray(unsigned char* data, uint width, uint height, uint depth, uint bpp) {
		glGenTextures(1,(GLuint*)&m_id);
		GLenum GLTarget = InitCreation(0);

		int channels	= bpp;
		GLenum format	= 0;

		switch(channels)
		{
		case 1: format = GL_LUMINANCE; break;
		case 2: format = GL_LUMINANCE_ALPHA; break;
		case 3: format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
		}

		m_width		= width;
		m_height	= height;
		m_bpp		= bpp;
		m_depth		= depth;

		if(m_target == textureTarget_1D) {
			glTexImage1D(GLTarget, 0, channels, width,0,format,GL_UNSIGNED_BYTE, data);
		}
		else if(m_target == textureTarget_2D) {
			glTexImage2D(GLTarget, 0, channels, width, height,0, format, GL_UNSIGNED_BYTE, data);
		}
		else if(m_target == textureTarget_3D) {
			glTexImage3D(GLTarget, 0, channels, width, height,depth,0, format, GL_UNSIGNED_BYTE, data);
		}

		if(m_useMipMaps && m_target != textureTarget_Rect && m_target != textureTarget_3D) {
			glGenerateMipmapEXT( GetGLTextureTargetEnum(m_target) );
		}

		PostCreation(GLTarget);

		return true;
	}

}