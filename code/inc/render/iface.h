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

#ifndef __IFACE_H__
#define __IFACE_H__

namespace rengine3d {

	class IFace {
	public:
		IFace(real a, real b, real c, CVec3 normal, CVec4 color, uint materialIndex);
	public:
		real		m_a;
		real		m_b;
		real		m_c;
		CVec3		m_normal;
		CVec4		m_color;
		CVec3		m_center;
		uint		m_material;
		vec3List_t	m_normals;
		vec3List_t	m_tangents;
		vec4List_t	m_colors;
	};

	r_inline IFace::IFace(real a, real b, real c, CVec3 normal, CVec4 color, uint materialIndex) {
		m_a			= a;
		m_b			= b;
		m_c			= c;
		m_normal	= normal;

		m_color		= color;
		m_material	= materialIndex;
	}

}

#endif
