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

#ifndef __IOBJECT3D_H__
#define __IOBJECT3D_H__

namespace rengine3d {

	class IObject3D: public INode {
	public:
		IObject3D();
		virtual ~IObject3D();
	protected:
		bool	m_visible;
		bool	m_frustumCulled;
		bool	m_castShadow;
		bool	m_receiveShadow;
		//bool	m_matrixAutoUpdate;
		//bool	m_rotationAutoUpdate;
		bool	m_matrixNeedsUpdate;

		CVec3	m_scale;
		CVec3	m_position;
		CVec3	m_rotation;
		//CVec3	m_eulerAngles;
		CQuat	m_quaternion;
		//CVec3	m_up;
		//CVec3	m_right;
		//CVec3	m_forward;

		CMat4	m_matrix;
		CMat4	m_relativeMatrix;
//		CMat4	m_worldMatrix;
	};


	r_inline IObject3D::IObject3D() {
		m_visible					= false;
		m_frustumCulled				= true;
		m_castShadow				= false;
		m_receiveShadow				= false;
		m_matrixNeedsUpdate			= true;

		m_scale						= CVec3(1,1,1);
	}

	r_inline IObject3D::~IObject3D() {
	}
}

#endif
