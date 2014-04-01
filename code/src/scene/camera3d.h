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

#ifndef __CCAMERA3D_H__
#define __CCAMERA3D_H__

namespace rengine3d {

	class CCamera3D: public ICamera3D {
	public:
		CCamera3D();
		CCamera3D(const string_t& name);
		CCamera3D(real fov, real aspect, real near, real far);
		virtual ~CCamera3D();

		virtual void UpdateProjectionMatrix(void);

		virtual real GetFov(void);
		virtual real GetAspect(void);
		virtual real GetNear(void);
		virtual real GetFar(void);

		virtual void SetFov(real fov);
		virtual void SetAspect(real aspect);
		virtual void SetNear(real near);
		virtual void SetFar(real far);

		virtual void SetModelViewMatrix(IRenderDriver* renderDriver);
		virtual void SetProjectionMatrix(IRenderDriver* renderDriver);

		virtual void SetLens(real focalLength, real frameHeight);
		virtual void SetViewOffset(real fullWidth, real fullHeight, real x, real y, real width, real height);

		virtual cameraType_t GetType(void) { return cameraType_3D; };
	private:
		real m_fov;
		real m_aspect;
		real m_near;
		real m_far;

	};

}

#endif
