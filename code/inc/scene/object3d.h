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

#ifndef __COBJECT3D_H__
#define __COBJECT3D_H__

namespace rengine3d {

	class CObject3D: public CNode {
	public:
		CObject3D();
		virtual ~CObject3D();

		void ApplyMatrix(CMat4 matrix);
		void UpdateMatrixWorld(bool force);
		void UpdateMatrix(void);

		void SetRotationFromAxisAngle(CVec3 axis, real angle);
		void SetRotationFromEuler(CVec3 euler);
		void SetRotationFromMatrix(CMat4 matrix);
		void SetRotationFromQuaternion(CQuat quat);

		void RotateOnAxis(CVec3 axis, real angle);
		void RotateX(real angle);
		void RotateY(real angle);
		void RotateZ(real angle);

		void TranslateOnAxis(CVec3 axis, real dist);
		void TranslateX(real dist);
		void TranslateY(real dist);
		void TranslateZ(real dist);

		CVec3 LocalToWorld(CVec3 pos);
		CVec3 WorldToLocal(CVec3 pos);

		void LookAt(CVec3 eye, CVec3 target, CVec3 up);

	protected:
		bool	m_visible;
		bool	m_frustumCulled;
		bool	m_castShadow;
		bool	m_receiveShadow;
		bool	m_matrixAutoUpdate;
		bool	m_rotationAutoUpdate;

		CVec3	m_scale;
		CVec3	m_position;
		CVec3	m_eulerAngles;
		CQuat	m_quaternion;
		CVec3	m_up;
		CVec3	m_right;
		CVec3	m_forward;

		CMat4	m_matrix;
		CMat4	m_worldMatrix;
	};


	r_inline CObject3D::CObject3D() {
		m_visible				= false;
		m_frustumCulled			= true;
		m_castShadow			= false;
		m_receiveShadow			= false;
		m_matrixAutoUpdate		= true;
		m_rotationAutoUpdate	= true;

		m_scale			= CVec3(1,1,1);

		m_up		= CVec3(0,1,0);
		m_forward	= CVec3(0,0,1);
		m_right		= CVec3(1,0,0);
	}

	r_inline CObject3D::~CObject3D() {
	}

	r_inline void CObject3D::ApplyMatrix(CMat4 matrix) {
		CMat4 mat = this->m_matrix * matrix;
		//this.matrix.multiplyMatrices( matrix, this.matrix );

	}

	r_inline void CObject3D::UpdateMatrixWorld(bool force) {
	}

	r_inline void CObject3D::UpdateMatrix(void) {
	}

	r_inline void CObject3D::SetRotationFromAxisAngle(CVec3 axis, real angle) {
	}

	r_inline void CObject3D::SetRotationFromEuler(CVec3 euler) {
	}

	r_inline void CObject3D::SetRotationFromMatrix(CMat4 matrix) {
	}

	r_inline void CObject3D::SetRotationFromQuaternion(CQuat quat) {
	}

	r_inline void CObject3D::RotateOnAxis(CVec3 axis, real angle) {
	}

	r_inline void CObject3D::RotateX(real angle) {
	}

	r_inline void CObject3D::RotateY(real angle) {
	}

	r_inline void CObject3D::RotateZ(real angle) {
	}

	r_inline void CObject3D::TranslateOnAxis(CVec3 axis, real dist) {
	}

	r_inline void CObject3D::TranslateX(real dist) {
	}

	r_inline void CObject3D::TranslateY(real dist) {
	}

	r_inline void CObject3D::TranslateZ(real dist) {
	}

	r_inline CVec3 CObject3D::LocalToWorld(CVec3 pos) {
	}

	r_inline CVec3 CObject3D::WorldToLocal(CVec3 pos) {
	}

	r_inline void CObject3D::LookAt(CVec3 eye, CVec3 target, CVec3 up) {
	}

}

#endif
