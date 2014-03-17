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

#ifndef __IRENDERDRIVER_H__
#define __IRENDERDRIVER_H__

namespace rengine3d {

	class IRenderDriver: public ISubSystem  {
	public:
		IRenderDriver(){};
		virtual ~IRenderDriver(){};

		virtual void Flush(void) = 0;
		virtual void SwapBuffers(void) = 0;

		virtual void ClearScreen(void) = 0;

		virtual bool SetDisplayMode(uint w, uint h, uint bpp, uint multiSampling, bool fs) = 0;
		virtual void SetFullScreen(bool fs) = 0;
		virtual bool GetFullScreen(void) = 0;

		virtual void SetWindowCaption(const string_t& caption) = 0;

		virtual void ShowCursor(bool show) = 0;

		virtual CVec2 GetScreenSize(void) = 0;
		virtual CVec2 GetVirtualSize(void) = 0;

		virtual int GetCaps(renderCaps_t rcaps) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual void SetMultisampling(bool enable) = 0;
		virtual void SetGammaCorrection(float value) = 0;
		virtual void SetClipPlane(int num, const CPlane& plane) = 0;
		virtual void SetClipPlaneActive(int num, bool active) = 0;
		virtual CPlane GetClipPlane(int num) = 0;

		virtual void SetMatrixMode(matrixMode_t mode) = 0;
		virtual void SetMatrix(matrixMode_t mode, const CMat4& mat) = 0;
		virtual void PushMatrix(matrixMode_t mode) = 0;
		virtual void PopMatrix(matrixMode_t mode) = 0;
		virtual void SetIdentityMatrix(matrixMode_t mode) = 0;
		virtual void TranslateMatrix(matrixMode_t mode, const CVec3 &pos) = 0;
		virtual void RotateMatrix(matrixMode_t mode, const CVec3 &rot) = 0;
		virtual void ScaleMatrix(matrixMode_t mode, const CVec3 &scale) = 0;

		virtual void SetOrthoProjection(const CVec2& size, float min, float max) = 0;

		virtual void SetColor(const CVec4& color) = 0;
		virtual void SetClearColor(const CVec4& color) = 0;
		virtual void SetClearDepth(float depth) = 0;
		virtual void SetClearStencil(int val) = 0;

		virtual void SetClearColorActive(bool active) = 0;
		virtual void SetClearDepthActive(bool active) = 0;
		virtual void SetClearStencilActive(bool active) = 0;

		virtual void SetScissorActive(bool active) = 0;
		virtual void SetScissorRect(int x, int y, int w, int h) = 0;

		virtual void SetStencilTwoSide(bool enable) = 0;
		virtual void SetCullActive(bool enable) = 0;
		virtual void SetCullMode(cullMode_t mode) = 0;

		virtual void SetBlendActive(bool active) = 0;
		virtual void SetBlendFunc(blendFunc_t src, blendFunc_t dst) = 0;

	};

}

#endif
