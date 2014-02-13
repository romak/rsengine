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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "sdl/SDL_config.h"
#include "sdl/SDL.h"
#include <SDL\SDL_opengl.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "renderdriver_sdl.h"

namespace rengine3d {

	CRenderDriverSDL::CRenderDriverSDL(IKernel* kernel) {
		m_width = 800;
		m_height = 600;
		m_bpp = 32;
		m_multiSampling = 0;
		m_fs = false;

		m_fileSys	= kernel->GetFileSystem();
		m_varSys	= kernel->GetVarSystem();
		m_sys		= kernel->GetSystem();
		m_window	= NULL;
	}

	CRenderDriverSDL::~CRenderDriverSDL() {
		this->Shutdown();
	}

	string_t CRenderDriverSDL::GetName(void) {
		return "CRenderDriverSDL";
	}

	string_t CRenderDriverSDL::GetDescription(void) {
		return "SDL render driver";
	}

	string_t CRenderDriverSDL::GetVersion(void) {
		return "0.0.2";
	}

	bool CRenderDriverSDL::Init() {
		Log("\tInitializing render driver SDL...\n");
		return true;
	}

	void CRenderDriverSDL::Shutdown(void) {
		Log("\tShutdown RenderDriverSDL...\n");
		SDL_VideoQuit();
	}

	bool CRenderDriverSDL::SetDisplayMode(uint w, uint h, uint bpp, uint multiSampling, bool fs) {
		m_width = w;
		m_height = h;
		m_bpp = bpp;
		m_multiSampling = multiSampling;
		m_fs = fs;

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		if(m_multiSampling > 0) {
			if(SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1)==-1) {
				Error("Multisample buffers not supported!\n");
			}
			else{
				if(SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, m_multiSampling)==-1) {
					Error("Couldn't set multisampling samples to %d\n", m_multiSampling);
				}
			}
		}

		unsigned int flags =  SDL_WINDOW_OPENGL;
		
		if(m_fs) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		
		Log("\tSetting video mode: %d x %d - %d bpp\n",m_width, m_height, m_bpp);

		m_window = SDL_CreateWindow("rsengine3d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);

		if (SDL_SetWindowDisplayMode(m_window, NULL) < 0) {
			Error("SetVideoMode failed in SDL_SetWindowDisplayMode: %dx%d:%d %d (\"%hs\")",w, h, bpp, fs ? 1 : 0, SDL_GetError());
			return false;
		}

		SDL_GLContext context = SDL_GL_CreateContext(m_window);
		if (!context){
			Error("SetVideoMode failed in SDL_GL_CreateContext: %dx%d:%d %d (\"%hs\")",w, h, bpp, fs? 1 : 0, SDL_GetError());
			return false;
		}

		if (m_fs){
			if (SDL_SetWindowFullscreen(m_window, flags) < 0)
			{
				Error("SetVideoMode failed in SDL_SetWindowFullscreen: %dx%d:%d %d (\"%hs\")",w, h, bpp, m_fs ? 1 : 0, SDL_GetError());
				return false;
			}
		}

		if (!m_fs)
			SDL_SetWindowSize(m_window, w, h);

		if (fs)
			SDL_SetWindowGrab(m_window, SDL_TRUE);
		else
			SDL_SetWindowGrab(m_window, SDL_FALSE);
			
		return true;
	}

	void CRenderDriverSDL::SetWindowCaption(const string_t& caption) {
		SDL_SetWindowTitle(m_window, caption.c_str());
	}

	void CRenderDriverSDL::ShowCursor(bool show) {
		SDL_ShowCursor(show);
	}


}


