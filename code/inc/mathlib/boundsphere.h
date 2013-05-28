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
#ifndef __CBOUNDSPHERE_H__
#define __CBOUNDSPHERE_H__

namespace rengine3d {

	class CBoundSphere {
	public:
		CBoundSphere();
		CBoundSphere(const CVec3& center, real radius);
		~CBoundSphere(){};

		void Draw(IRenderDriver* renderDriver);
	public:
		CVec3	m_center;
		real	m_radius;
	};

	r_inline CBoundSphere::CBoundSphere(): m_radius(0) {
	}

	r_inline CBoundSphere::CBoundSphere(const CVec3& center, real radius): m_center(center), m_radius(radius) {
	}

	r_inline void CBoundSphere::Draw(IRenderDriver* renderDriver) {
	}

}

#endif