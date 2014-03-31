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

		virtual void ApplyMatrix(CMat4 matrix);
		virtual void UpdateMatrixWorld(bool force);
		virtual void UpdateMatrix(void);

		virtual void SetRotationFromAxisAngle(const CVec3& axis, real angle);
		virtual void SetRotationFromEuler(CVec3 euler);
		virtual void SetRotationFromMatrix(CMat4 matrix);
		virtual void SetRotationFromQuaternion(CQuat quat);

		virtual void RotateOnAxis(CVec3 axis, real angle);
		virtual void RotateX(real angle);
		virtual void RotateY(real angle);
		virtual void RotateZ(real angle);

		virtual void TranslateOnAxis(CVec3 axis, real dist);
		virtual void TranslateX(real dist);
		virtual void TranslateY(real dist);
		virtual void TranslateZ(real dist);

		virtual void LookAt(CVec3 eye, CVec3 target, CVec3 up);

		CVec3 LocalToWorld(CVec3 pos);
		CVec3 WorldToLocal(CVec3 pos);
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

//		CTransform	m_transform;
	};


	r_inline IObject3D::IObject3D() {
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

	r_inline IObject3D::~IObject3D() {
	}

	r_inline void IObject3D::ApplyMatrix(CMat4 matrix) {
		CMat4 mat = this->m_matrix * matrix;
		//this.matrix.multiplyMatrices( matrix, this.matrix );

	}

	r_inline void IObject3D::UpdateMatrixWorld(bool force) {
	}

	r_inline void IObject3D::UpdateMatrix(void) {
	}

	r_inline void IObject3D::SetRotationFromAxisAngle(const CVec3& axis, real angle) {
		m_quaternion.SetFromAxisAngle(axis, angle);

	}

	r_inline void IObject3D::SetRotationFromEuler(CVec3 euler) {
	}

	r_inline void IObject3D::SetRotationFromMatrix(CMat4 matrix) {
//		m_quaternion.SetFromRotationMatrix(matrix);
	}

	r_inline void IObject3D::SetRotationFromQuaternion(CQuat quat) {
		m_quaternion = quat;
	}

	r_inline void IObject3D::RotateOnAxis(CVec3 axis, real angle) {
//		CQuat q1;
//		q1.SetFromAxisAngle(axis, angle);
//		m_quaternion *= q1;

	}

	r_inline void IObject3D::RotateX(real angle) {
		this->RotateOnAxis(CVec3(1,0,0), angle);
	}

	r_inline void IObject3D::RotateY(real angle) {
		this->RotateOnAxis(CVec3(0,1,0), angle);
	}

	r_inline void IObject3D::RotateZ(real angle) {
		this->RotateOnAxis(CVec3(0,0,1), angle);
	}

	r_inline void IObject3D::TranslateOnAxis(CVec3 axis, real dist) {
	}

	r_inline void IObject3D::TranslateX(real dist) {
	}

	r_inline void IObject3D::TranslateY(real dist) {
	}

	r_inline void IObject3D::TranslateZ(real dist) {
	}

	r_inline CVec3 IObject3D::LocalToWorld(CVec3 pos) {
	}

	r_inline CVec3 IObject3D::WorldToLocal(CVec3 pos) {
	}

	r_inline void IObject3D::LookAt(CVec3 eye, CVec3 target, CVec3 up) {
	}

}

#endif
