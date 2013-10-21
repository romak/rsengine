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

#ifndef __IRENDERVERTEX_H__
#define __IRENDERVERTEX_H__

namespace rengine3d {

	class IRenderVertex {
	public:
		IRenderVertex();
		virtual ~IRenderVertex();
	public:
		bool	m_visible;
		CVec3	m_posWorld;
		CVec4	m_posScreen;
	};

	r_inline IRenderVertex::IRenderVertex() {
		m_visible = false;
	}

	r_inline IRenderVertex::~IRenderVertex() {
	}

}

#endif
