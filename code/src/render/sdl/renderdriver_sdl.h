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

#ifndef __CRENDERDRIVERSDL_H__
#define __CRENDERDRIVERSDL_H__

namespace rengine3d {

	class CRenderDriverSDL: public IRenderDriver {
	public:
		CRenderDriverSDL(IKernel* kernel);
		virtual ~CRenderDriverSDL();

		virtual bool Init();
		virtual void Shutdown(void);

		virtual void SwapBuffers(void);
		virtual void FlushRendering(void);

		virtual void ClearScreen(void);

		virtual bool SetDisplayMode(uint w, uint h, uint bpp, uint multiSampling, bool fs);
		virtual void SetFullScreen(bool fs);
		virtual bool GetFullScreen(void);

		virtual void SetWindowCaption(const string_t& caption);

		virtual void ShowCursor(bool show);

		virtual CVec2 GetScreenSize(void);
		virtual CVec2 GetVirtualSize(void);

		virtual int GetCaps(renderCaps_t rcaps);

		virtual void SetVSync(bool enable);
		virtual void SetMultisampling(bool enable);
		virtual void SetGammaCorrection(float value);
		virtual void SetClipPlane(int num, const CPlane& plane);
		virtual void SetClipPlaneActive(int num, bool active);
		virtual CPlane GetClipPlane(int num);

		virtual void SetMatrixMode(matrixMode_t mode);
		virtual void SetMatrix(matrixMode_t mode, const CMat4& mat);
		virtual void PushMatrix(matrixMode_t mode);
		virtual void PopMatrix(matrixMode_t mode);
		virtual void SetIdentityMatrix(matrixMode_t mode);
		virtual void TranslateMatrix(matrixMode_t mode, const CVec3 &pos);
		virtual void RotateMatrix(matrixMode_t mode, const CVec3 &rot);
		virtual void ScaleMatrix(matrixMode_t mode, const CVec3 &scale);

		virtual void SetOrthoProjection(const CVec2& size, float min, float max);

		virtual void SetColor(const CVec4& color);

		virtual void SetClearColor(const CVec4& color);
		virtual void SetClearDepth(float depth);
		virtual void SetClearStencil(int val);

		virtual void SetClearColorActive(bool active);
		virtual void SetClearDepthActive(bool active);
		virtual void SetClearStencilActive(bool active);

		virtual void SetScissorActive(bool active);
		virtual void SetScissorRect(int x, int y, int w, int h);

		virtual void SetStencilTwoSide(bool enable);
		virtual void SetCullActive(bool enable);
		virtual void SetCullMode(cullMode_t mode);

		virtual void SetBlendActive(bool active);
		virtual void SetBlendFunc(blendFunc_t src, blendFunc_t dst);

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);
	private:
		void SetupOpenGL();
		uint GetGLBlendEnum(blendFunc_t func);
	private:
		uint			m_width;
		uint			m_height;
		uint			m_bpp;
		uint			m_multiSampling;
		bool			m_fs;

		bool			m_clearColor;
		bool			m_clearDepth;
		bool			m_clearStencil;

		IKernel*		m_kernel;
		IFileSystem*	m_fileSys;
		IVarSystem*		m_varSys;
		ISystem*		m_sys;

		SDL_Surface*	m_screen;
		SDL_Window*		m_window;
		SDL_GLContext	m_context;
		CVec2			m_screenSize;
		CVec2			m_virtualSize;

		CPlane			m_clipPlanes[MAX_CLIP_PLANES];
	};
}

#endif
