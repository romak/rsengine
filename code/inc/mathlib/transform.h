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

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

namespace rengine3d {

	class CTransform {
	public:
		CTransform();

		void SetPosition(const CVec3& pos);
		void SetRotation(const CQuat& rot);
		void SetScale(const CVec3& scale);

		const CVec3& GetPosition(void);
		const CQuat& GetRotation(void);
		const CVec3& GetScale(void);
		const CMat4& GetMatrix(void);

		bool IsNeedUpdate(void);
	public:
		CVec3		m_position;
		CQuat		m_rotation;
		CVec3		m_scale;
		CVec3		m_eulerAngles;

		CVec3		m_localPosition;
		CQuat		m_localRotation;
		CVec3		m_localScale;
		CVec3		m_localEulerAngles;

		CMat4		m_worldToLocalMatrix;
		CVec3		m_forward;
		CVec3		m_right;
		CVec3		m_up;
		//CTransform	m_parent;
		bool		m_needUpdate;
	};

	r_inline CTransform::CTransform() {
		m_needUpdate = true;
		m_scale.Set(1.0f, 1.0f, 1.0f);
	}

	r_inline void CTransform::SetPosition(const CVec3& pos) {
		m_position		= pos;
		m_needUpdate	= true;
	}

	r_inline void CTransform::SetRotation(const CQuat& rot) {
		m_rotation		= rot;
		m_needUpdate	= true;
	}

	r_inline void CTransform::SetScale(const CVec3& scale) {
		m_scale			= scale;
		m_needUpdate	= true;
	}

	r_inline const CVec3& CTransform::GetPosition(void) {
		return  m_position;
	}

	r_inline const CQuat& CTransform::GetRotation(void){
		return m_rotation;
	}

	r_inline const CVec3& CTransform::GetScale(void){
		return m_scale;
	}

	r_inline const CMat4& CTransform::GetMatrix(void) {

		// Recalc matrix
		if (m_needUpdate) {
			m_worldToLocalMatrix		= m_rotation.ToMatrix4();
			m_worldToLocalMatrix[3][0]	= m_position.x;
			m_worldToLocalMatrix[3][1]	= m_position.y;
			m_worldToLocalMatrix[3][2]	= m_position.z;

			m_needUpdate = false;
		}

		return m_worldToLocalMatrix;
	}

	r_inline bool CTransform::IsNeedUpdate(void) {
		return m_needUpdate;
	}

}

#endif