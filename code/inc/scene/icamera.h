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

#ifndef __ICAMERA_H__
#define __ICAMERA_H__

namespace rengine3d {

	typedef enum 
	{
		cameraType_2D,
		cameraType_3D,
		cameraType_Last
	}cameraType_t;

	class ICamera: public IObject3D {
	public:
		ICamera(){};
		virtual ~ICamera(){};

		virtual cameraType_t GetType(void) = 0;
	};
}

#endif
