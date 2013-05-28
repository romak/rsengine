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

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

namespace rengine3d {

	class CTransform {
	public:
		CTransform();
		void SetPosition(const CVec3& pos);
		void SetRotate(const CQuat& rot);
		void SetScale(const CVec3& scale);

		const CVec3& GetPosition(void);
		const CQuat& GetRotate(void);
		const CVec3& GetScale(void);
		const CMat4& GetMatrix(void);

		bool IsNeedUpdate(void);
	protected:
		CVec3	m_position;
		CQuat	m_rotate;
		CVec3	m_scale;
		CMat4	m_matrix;
		bool	m_needUpdate;
	};

	r_inline CTransform::CTransform() {
		m_needUpdate = true;
		m_scale.Set(1.0f, 1.0f, 1.0f);
	}

	r_inline void CTransform::SetPosition(const CVec3& pos) {
		m_position		= pos;
		m_needUpdate	= true;
	}

	r_inline void CTransform::SetRotate(const CQuat& rot) {
		m_rotate		= rot;
		m_needUpdate	= true;
	}

	r_inline void CTransform::SetScale(const CVec3& scale) {
		m_scale			= scale;
		m_needUpdate	= true;
	}

	r_inline const CVec3& CTransform::GetPosition(void) {
		return  m_position;
	}

	r_inline const CQuat& CTransform::GetRotate(void){
		return m_rotate;
	}

	r_inline const CVec3& CTransform::GetScale(void){
		return m_scale;
	}

	r_inline const CMat4& CTransform::GetMatrix(void) {

		// Recalc matrix
		if (m_needUpdate) {
			m_matrix		= m_rotate.ToMatrix4();
			m_matrix[3][0]	= m_position.x;
			m_matrix[3][1]	= m_position.y;
			m_matrix[3][2]	= m_position.z;

			m_needUpdate = false;
		}

		return m_matrix;
	}

	r_inline bool CTransform::IsNeedUpdate(void) {
		return m_needUpdate;
	}

}

#endif