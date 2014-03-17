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
#include "../kernel/enginevars.h"
#include "sdl/SDL_config.h"
#include "sdl/SDL.h"
#include <SDL\SDL_opengl.h>
#include "renderdriver_sdl.h"

#if PLATFORM == PLATFORM_WIN32
#pragma comment(lib, "OpenGL32.lib")
#endif

namespace rengine3d {

	CRenderDriverSDL::CRenderDriverSDL(IKernel* kernel) {
		m_width			= 800;
		m_height		= 600;
		m_screenSize	= CVec2((real)m_width, (real)m_height);
		m_virtualSize	= CVec2(800.0, 600.0);

		m_bpp			= 32;
		m_multiSampling = 0;
		m_fs			= false;

		m_fileSys		= kernel->GetFileSystem();
		m_varSys		= kernel->GetVarSystem();
		m_sys			= kernel->GetSystem();
		m_window		= NULL;

		m_clearColor	= true;
		m_clearDepth	= true;
		m_clearStencil	= false;
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
		m_initialized = true;
		return m_initialized;
	}

	void CRenderDriverSDL::Shutdown(void) {
		Log("\tShutdown RenderDriverSDL...\n");
		SDL_VideoQuit();
		m_initialized = false;
	}

	bool CRenderDriverSDL::SetDisplayMode(uint w, uint h, uint bpp, uint multiSampling, bool fs) {
		m_width = w;
		m_height = h;
		m_bpp = bpp;
		m_multiSampling = multiSampling;
		m_fs = fs;
		m_screenSize	= CVec2((real)m_width, (real)m_height);

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

		Log("Setting video mode: %d x %d - %d bpp\n",m_width, m_height, m_bpp);

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

		SetupOpenGL();

		this->SetVSync(v_sync.GetBool());

		SDL_GL_SwapWindow(m_window);

		return true;
	}

	void CRenderDriverSDL::SetFullScreen(bool fs) {
		unsigned int flags =  SDL_WINDOW_OPENGL;
		m_fs = fs;
		if (fs) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			SDL_SetWindowFullscreen(m_window, flags);
			SDL_SetWindowGrab(m_window, SDL_TRUE);
			SDL_ShowCursor(false);
		}else {
			flags |= SDL_WINDOW_RESIZABLE;
			SDL_SetWindowFullscreen(m_window, flags);
			SDL_SetWindowSize(m_window, m_width, m_height);
			SDL_SetWindowGrab(m_window, SDL_FALSE);
		}
		SDL_GL_SwapWindow(m_window);
	}

	bool CRenderDriverSDL::GetFullScreen(void) {
		return m_fs;
	}

	void CRenderDriverSDL::SetupOpenGL() {
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST); 
		glDepthFunc(GL_LEQUAL); 
		glDisable(GL_ALPHA_TEST);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glClearStencil(0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glEnableClientState(GL_VERTEX_ARRAY ); 
		glEnableClientState(GL_COLOR_ARRAY ); 
		glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_INDEX_ARRAY); 
		glDisableClientState(GL_EDGE_FLAG_ARRAY);

		Log("\tGraphics card capabilities:\n");
		Log("\t\tVertex Buffer Object: %d\n",GetCaps(renderCaps_VertexBufferObject));
		Log("\t\tMax texture image units: %d\n",GetCaps(renderCaps_MaxTextureImageUnits));
		Log("\t\tMax texture coord units: %d\n",GetCaps(renderCaps_MaxTextureCoordUnits));
		Log("\t\tTwo sided stencil: %d\n",GetCaps(renderCaps_TwoSideStencil));
		Log("\t\tAnisotropic filtering: %d\n",GetCaps(renderCaps_AnisotropicFiltering));
		if(GetCaps(renderCaps_AnisotropicFiltering))
			Log("\t\tMax Anisotropic degree: %d\n",GetCaps(renderCaps_MaxAnisotropicFiltering));
		Log("\t\tMultisampling: %d\n",GetCaps(renderCaps_Multisampling));
		Log("\t\tVertex Program: %d\n",GetCaps(renderCaps_GL_VertexProgram));
		Log("\t\tFragment Program: %d\n",GetCaps(renderCaps_GL_FragmentProgram));
	}

	void CRenderDriverSDL::Flush(void) {
		glFlush();
	}

	void CRenderDriverSDL::SwapBuffers(void) {
		glFlush();
		SDL_GL_SwapWindow(m_window);
	}

	void CRenderDriverSDL::ClearScreen(void) {
		GLbitfield bitmask=0;

		if(m_clearColor) 
			bitmask |= GL_COLOR_BUFFER_BIT;

		if(m_clearDepth)
			bitmask |= GL_DEPTH_BUFFER_BIT;

		if(m_clearStencil)
			bitmask |= GL_STENCIL_BUFFER_BIT;

		glClear(bitmask);
	}

	void CRenderDriverSDL::SetWindowCaption(const string_t& caption) {
		SDL_SetWindowTitle(m_window, caption.c_str());
	}

	void CRenderDriverSDL::ShowCursor(bool show) {
		SDL_ShowCursor(show);
	}

	CVec2 CRenderDriverSDL::GetScreenSize(void) {
		return m_screenSize;
	}

	CVec2 CRenderDriverSDL::GetVirtualSize(void) {
		return m_virtualSize;
	}

	void CRenderDriverSDL::SetVSync(bool enable) {
		SDL_GL_SetSwapInterval(enable);		
	}

	void CRenderDriverSDL::SetMultisampling(bool enable) {
		if(!GL_ARB_multisample || m_multiSampling<=0) 
			return;

		if(enable)
			glEnable(GL_MULTISAMPLE_ARB);
		else
			glDisable(GL_MULTISAMPLE_ARB);
	}

	void CRenderDriverSDL::SetGammaCorrection(float value) {
		SDL_SetWindowBrightness(m_window,value);
	}

	void CRenderDriverSDL::SetClipPlane(int num, const CPlane& plane) {
		m_clipPlanes[num] = plane;

		double cplane[4];
		cplane[0] = plane.m_normal.x;
		cplane[1] = plane.m_normal.y;
		cplane[2] = plane.m_normal.z;
		cplane[3] = plane.m_distance;
		glClipPlane(GL_CLIP_PLANE0 + num, cplane);
	}

	void CRenderDriverSDL::SetClipPlaneActive(int num, bool active) {
		if(active) 
			glEnable(GL_CLIP_PLANE0 + num);
		else	
			glDisable(GL_CLIP_PLANE0 + num);
	}

	CPlane CRenderDriverSDL::GetClipPlane(int num) {
		return m_clipPlanes[num];
	}

	void CRenderDriverSDL::SetMatrixMode(matrixMode_t mode) {
		switch(mode)
		{
		case matrixType_ModelView:	glMatrixMode(GL_MODELVIEW);break;
		case matrixType_Projection: glMatrixMode(GL_PROJECTION); break;
		case matrixType_Texture:	glMatrixMode(GL_TEXTURE); break;
		}
	}

	void CRenderDriverSDL::SetMatrix(matrixMode_t mode, const CMat4& mat) {
	}

	void CRenderDriverSDL::PushMatrix(matrixMode_t mode) {
		SetMatrixMode(mode);
		glPushMatrix();
	}

	void CRenderDriverSDL::PopMatrix(matrixMode_t mode) {
		SetMatrixMode(mode);
		glPopMatrix();
	}

	void CRenderDriverSDL::SetIdentityMatrix(matrixMode_t mode) {
		SetMatrixMode(mode);
		glLoadIdentity();
	}

	void CRenderDriverSDL::TranslateMatrix(matrixMode_t mode, const CVec3 &pos) {
		SetMatrixMode(mode);
		glTranslatef(pos.x,pos.y,pos.z);
	}

	void CRenderDriverSDL::RotateMatrix(matrixMode_t mode, const CVec3 &rot) {
		SetMatrixMode(mode);
		glRotatef(1,rot.x,rot.y,rot.z);
	}

	void CRenderDriverSDL::ScaleMatrix(matrixMode_t mode, const CVec3 &scale) {
		SetMatrixMode(mode);
		glScalef(scale.x,scale.y,scale.z);
	}

	void CRenderDriverSDL::SetOrthoProjection(const CVec2& size, float min, float max) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,size.x,size.y,0,min,max);
	}

	void CRenderDriverSDL::SetColor(const CVec4& color) {
		glColor4f(color.x, color.y, color.z, color.w);
	}

	void CRenderDriverSDL::SetClearColor(const CVec4& color) {
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void CRenderDriverSDL::SetClearDepth(float depth) {
		glClearDepth(depth);
	}

	void CRenderDriverSDL::SetClearStencil(int val) {
		glClearStencil(val);
	}

	void CRenderDriverSDL::SetClearColorActive(bool active) {
		m_clearColor = active;
	}

	void CRenderDriverSDL::SetClearDepthActive(bool active) {
		m_clearDepth = active;
	}

	void CRenderDriverSDL::SetClearStencilActive(bool active) {
		m_clearStencil = active;
	}

	void CRenderDriverSDL::SetScissorActive(bool active) {
		if(active) 
			glEnable(GL_SCISSOR_TEST);
		else 
			glDisable(GL_SCISSOR_TEST);
	}

	void CRenderDriverSDL::SetScissorRect(int x, int y, int w, int h) {
		glScissor(x, (int)(m_screenSize.y - y - 1)-h, w, h);
	}

	void CRenderDriverSDL::SetStencilTwoSide(bool enable) {
		if(GL_EXT_stencil_two_side)
		{
			if (enable)
				glEnable(GL_STENCIL_TEST_TWO_SIDE_EXT);
			else
				glDisable(GL_STENCIL_TEST_TWO_SIDE_EXT);
		}
	}

	void CRenderDriverSDL::SetCullActive(bool enable) {
		if(enable) 
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);

		glCullFace(GL_BACK);
	}

	void CRenderDriverSDL::SetCullMode(cullMode_t mode) {
		glCullFace(GL_BACK);
		if(mode == cullMode_Clockwise) 
			glFrontFace(GL_CCW);
		else							
			glFrontFace(GL_CW);
	}

	void CRenderDriverSDL::SetBlendActive(bool active) {
		if(active)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}

	void CRenderDriverSDL::SetBlendFunc(blendFunc_t src, blendFunc_t dst) {
		glBlendFunc(GetGLBlendEnum(src),GetGLBlendEnum(dst));
	}

	uint CRenderDriverSDL::GetGLBlendEnum(blendFunc_t func) {
		switch(func) {
		case blendFunc_Zero:					return GL_ZERO;
		case blendFunc_One:						return GL_ONE;
		case blendFunc_SrcColor:				return GL_SRC_COLOR;
		case blendFunc_OneMinusSrcColor:		return GL_ONE_MINUS_SRC_COLOR;
		case blendFunc_DestColor:				return GL_DST_COLOR;
		case blendFunc_OneMinusDestColor:		return GL_ONE_MINUS_DST_COLOR;
		case blendFunc_SrcAlpha:				return GL_SRC_ALPHA;
		case blendFunc_OneMinusSrcAlpha:		return GL_ONE_MINUS_SRC_ALPHA;
		case blendFunc_DestAlpha:				return GL_DST_ALPHA;
		case blendFunc_OneMinusDestAlpha:		return GL_ONE_MINUS_DST_ALPHA;
		case blendFunc_SrcAlphaSaturate:		return GL_SRC_ALPHA_SATURATE;
		}
		return 0;
	}

	int CRenderDriverSDL::GetCaps(renderCaps_t rcaps) {
		switch(rcaps) {

		case renderCaps_VertexBufferObject:	
			{
				return GL_ARB_vertex_buffer_object?1:0;
			}
		case renderCaps_TwoSideStencil:	
			{
				if(GL_EXT_stencil_two_side) return 1;
				else if(GL_ATI_separate_stencil) return 1;
				else return 0;
			}
		case renderCaps_MaxTextureImageUnits:	
			{
				int units;
				glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS_ARB,(GLint *)&units);
				return units;
			}
		case renderCaps_MaxTextureCoordUnits:	
			{
				int units;
				glGetIntegerv(GL_MAX_TEXTURE_COORDS_ARB,(GLint *)&units);
				return units;
			}
		case renderCaps_AnisotropicFiltering:	
			{
				return GL_EXT_texture_filter_anisotropic?1:0;
			}
		case renderCaps_MaxAnisotropicFiltering:	
			{
				if(!GL_EXT_texture_filter_anisotropic) return 0;

				float max;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&max);
				return (int)max;
			}
		case renderCaps_Multisampling:	
			{
				return GL_ARB_multisample?1:0;
			}
		case renderCaps_GL_VertexProgram:	
			{
				return GL_ARB_vertex_program?1:0;
			}
		case renderCaps_GL_FragmentProgram:
			{
				return GL_ARB_fragment_program?1:0;
			}
		}

		return 0;
	}

}


