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

#ifndef __ICAMERA3D_H__
#define __ICAMERA3D_H__

namespace rengine3d {

	class ICamera3D: public ICamera {
	public:
		ICamera3D(){};
		ICamera3D(real fov, real aspect, real near, real far){};
		virtual ~ICamera3D(){};

		virtual void UpdateProjectionMatrix(void) = 0;

		virtual real GetFov(void) = 0;
		virtual real GetAspect(void) = 0;
		virtual real GetNear(void) = 0;
		virtual real GetFar(void) = 0;

		virtual void SetFov(real fov) = 0;
		virtual void SetAspect(real aspect) = 0;
		virtual void SetNear(real near) = 0;
		virtual void SetFar(real far) = 0;

		/**
		* Uses Focal Length (in mm) to estimate and set FOV
		* 35mm (fullframe) camera is used if frame size is not specified;
		* Formula based on http://www.bobatkins.com/photography/technical/field_of_view.html
		*/
		virtual void SetLens(real focalLength, real frameHeight) = 0;

		/**
		* Sets an offset in a larger frustum. This is useful for multi-window or
		* multi-monitor/multi-machine setups.
		*
		* For example, if you have 3x2 monitors and each monitor is 1920x1080 and
		* the monitors are in grid like this
		*
		*   +---+---+---+
		*   | A | B | C |
		*   +---+---+---+
		*   | D | E | F |
		*   +---+---+---+
		*
		* then for each monitor you would call it like this
		*
		*   var w = 1920;
		*   var h = 1080;
		*   var fullWidth = w * 3;
		*   var fullHeight = h * 2;
		*
		*   --A--
		*   camera.SetViewOffset( fullWidth, fullHeight, w * 0, h * 0, w, h );
		*   --B--
		*   camera.SetViewOffset( fullWidth, fullHeight, w * 1, h * 0, w, h );
		*   --C--
		*   camera.SetViewOffset( fullWidth, fullHeight, w * 2, h * 0, w, h );
		*   --D--
		*   camera.SetViewOffset( fullWidth, fullHeight, w * 0, h * 1, w, h );
		*   --E--
		*   camera.SetViewOffset( fullWidth, fullHeight, w * 1, h * 1, w, h );
		*   --F--
		*   camera.SetViewOffset( fullWidth, fullHeight, w * 2, h * 1, w, h );
		*/

		virtual void SetViewOffset(real fullWidth, real fullHeight, real x, real y, real width, real height) = 0;

	};
}

#endif
