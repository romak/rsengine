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

#ifndef __CQUAT_H__
#define __CQUAT_H__

namespace rengine3d {
	class CVec3;
	class CQuat {
	public:
		CQuat();
		CQuat(real x, real y, real z, real w);

		CQuat operator + (const CQuat& quat) const;
		CQuat &operator += (const CQuat& quat);
		CQuat operator - (const CQuat& quat) const;
		CQuat &operator -= (const CQuat& quat);
		CQuat operator * (const CQuat& quat) const;
		CQuat &operator *= (const CQuat& quat);
		CQuat operator * (real factor) const;

		real Dot(const CQuat& quat) const;
		void SetFromAxisAngle(const CVec3& axis, real angle);
		void SetFromEulerAngles (real x, real y, real z);
		void SetFromRotationMatrix(const CMat4 &m);
		void SetToAxisAngle(CVec3& axis, real& angle);
		void Slerp(const CQuat& from, const CQuat& to, real ratio);
		void Nlerp(const CQuat& from, const CQuat& to, real ratio);
		void Normalize(void);
		CQuat GetInverse(void) const;
		CVec3 Rotate(const CVec3& vec) const;
		void ToMatrix(CMat4& result) const;
		CMat4 ToMatrix (void) const;
		void Identity(void);
	public:
		CVec3	m_v;
		real	m_w;
	};

	r_inline CQuat::CQuat() {
		m_w = 1.0f;
	}

	r_inline CQuat::CQuat(real x, real y, real z, real w) {
		m_v.Set(x,y,z); m_w = w;
	}

	r_inline CQuat CQuat::operator + (const CQuat& quat) const {
		CQuat temp;
		temp.m_w = m_w + quat.m_w;
		temp.m_v = m_v + quat.m_v;
		return temp;
	}

	r_inline CQuat &CQuat::operator -= (const CQuat& quat) {
		*this = *this - quat;
		return *this;
	}

	r_inline CQuat CQuat::operator - (const CQuat& quat) const {
		CQuat temp;
		temp.m_w = m_w - quat.m_w;
		temp.m_v = m_v - quat.m_v;
		return temp;
	}

	r_inline CQuat &CQuat::operator += (const CQuat& quat) {
		*this = *this + quat;
		return *this;
	}

	r_inline CQuat CQuat::operator * (const CQuat& quat) const {
		CQuat temp;
		temp.m_w = (m_w * quat.m_w) - (m_v.Dot(quat.m_v));
		temp.m_v = (m_v.Cross(quat.m_v)) + (quat.m_v * m_w) + (m_v * quat.m_w);
		return temp;
	}

	r_inline CQuat& CQuat::operator *= (const CQuat& quat) {
		*this = *this * quat;
		return *this;
	}

	r_inline CQuat CQuat::operator * (real factor) const {
		CQuat temp;
		temp.m_w = m_w * factor;
		temp.m_v = m_v * factor;
		return temp;
	}

	r_inline real CQuat::Dot(const CQuat& quat) const {
		return
			m_v.x * quat.m_v.x +
			m_v.y * quat.m_v.y +
			m_v.z * quat.m_v.z +
			m_w   * quat.m_w;
	}

	r_inline void CQuat::SetFromAxisAngle(const CVec3& axis, real angle) {
		real sinHalfTheta=(real) sin(angle/2);
		real cosHalfTheta=(real) cos(angle/2);

		m_v.x = axis.x * sinHalfTheta;
		m_v.y = axis.y * sinHalfTheta;
		m_v.z = axis.z * sinHalfTheta;
		m_w = cosHalfTheta;
	}

	r_inline void CQuat::SetToAxisAngle(CVec3& axis, real& angle) {
		CQuat q = *this;
		q.Normalize();
		angle = acosf(q.m_w) * 2.f;
		real  sin_a = sqrtf(1.f - q.m_w * q.m_w);
		if (fabsf(sin_a) < 0.0005f) sin_a = 1.f;
		axis.x = q.m_v.x / sin_a;
		axis.y = q.m_v.y / sin_a;
		axis.z = q.m_v.z / sin_a;
	}

	r_inline void CQuat::SetFromEulerAngles (real x, real y, real z) {
		real cr, cp, cy;
		real sr, sp, sy;
		CQuat roll, pitch, yaw;

		cr = cosf(x * 0.5f);
		cp = cosf(y * 0.5f);
		cy = cosf(z * 0.5f);

		sr = sinf(x * 0.5f);
		sp = sinf(y * 0.5f);
		sy = sinf(z * 0.5f);

		roll.m_v = CVec3(sr, 0, 0);
		roll.m_w = cr;

		pitch.m_v = CVec3(0, sp, 0);
		pitch.m_w = cp;

		yaw.m_v = CVec3(0, 0, sy);
		yaw.m_w = cy;

		(*this) = yaw * pitch * roll;
	}

	r_inline void CQuat::SetFromRotationMatrix(const CMat4 &m) {
		// Creates a quaternion from a rotation matrix. 
		// The algorithm used is from Allan and Mark Watt's "Advanced 
		// Animation and Rendering Techniques" (ACM Press 1992).

		real s = 0.0f;
		real q[4] = {0.0f};
		real trace = m[0][0] + m[1][1] + m[2][2];

		if (trace > 0.0f)
		{
			s = sqrtf(trace + 1.0f);
			q[3] = s * 0.5f;
			s = 0.5f / s;
			q[0] = (m[1][2] - m[2][1]) * s;
			q[1] = (m[2][0] - m[0][2]) * s;
			q[2] = (m[0][1] - m[1][0]) * s;
		}
		else
		{
			int nxt[3] = {1, 2, 0};
			int i = 0, j = 0, k = 0;

			if (m[1][1] > m[0][0])
				i = 1;

			if (m[2][2] > m[i][i])
				i = 2;

			j = nxt[i];
			k = nxt[j];
			s = sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);

			q[i] = s * 0.5f;
			s = 0.5f / s;
			q[3] = (m[j][k] - m[k][j]) * s;
			q[j] = (m[i][j] + m[j][i]) * s;
			q[k] = (m[i][k] + m[k][i]) * s;
		}

		m_v.x = q[0]; m_v.y = q[1]; m_v.z = q[2]; m_w = q[3];
	}

	r_inline void CQuat::Slerp(const CQuat& from, const CQuat& to, real ratio) {
		real to1[4];
		real omega, cosom, sinom, scale0, scale1;

		cosom = from.Dot(to);

		if (cosom < 0.0) {
			cosom = -cosom;
			to1[0] = -to.m_v.x;
			to1[1] = -to.m_v.y;
			to1[2] = -to.m_v.z;
			to1[3] = -to.m_w;
		} else {
			to1[0] = to.m_v.x;
			to1[1] = to.m_v.y;
			to1[2] = to.m_v.z;
			to1[3] = to.m_w;
		}

		if ((1.0f - cosom) > EPSILON) {
			// standard case (slerp)
			omega = acosf(cosom);
			sinom = sinf(omega);
			scale0 = sinf((1.0f - ratio) * omega) / sinom;
			scale1 = sinf(ratio * omega) / sinom;
		} else {
			// "from" and "to" quaternions are very close 
			//  ... so we can do a linear interpolation
			scale0 = 1.0f - ratio;
			scale1 = ratio;
		}

		// calculate final values
		m_v.x = scale0 * from.m_v.x + scale1 * to1[0];
		m_v.y = scale0 * from.m_v.y + scale1 * to1[1];
		m_v.z = scale0 * from.m_v.z + scale1 * to1[2];
		m_w	  = scale0 * from.m_w + scale1 * to1[3];
	}

	r_inline void CQuat::Nlerp(const CQuat& from, const CQuat& to, real ratio) {
		real c = from.Dot(to);
		if (c < 0.f)
			*this = from - (to + from) * ratio;
		else
			*this = from + (to - from) * ratio;

		Normalize();
	}

	r_inline void CQuat::Normalize(void) {
		real lensqrd = SQR(m_v.x) + SQR(m_v.y) + SQR(m_v.z) + SQR(m_w);
		if (lensqrd > 0) {
			real invlen=1.0f/sqrtf(lensqrd);
			m_v *= invlen;
			m_w *= invlen;
		}
	}

	r_inline CQuat CQuat::GetInverse(void) const {
		return CQuat(-m_v.x, -m_v.y, -m_v.z, m_w);
	}

	r_inline void CQuat::ToMatrix(CMat4& result) const {
		real wx, wy, wz, xx, xy, xz, yy, yz, zz;

		xx = m_v.x * m_v.x * 2.f;
		xy = m_v.x * m_v.y * 2.f;
		xz = m_v.x * m_v.z * 2.f;

		yy = m_v.y * m_v.y * 2.f;
		yz = m_v.y * m_v.z * 2.f;

		zz = m_v.z * m_v.z * 2.f;

		wx = m_w * m_v.x * 2.f;
		wy = m_w * m_v.y * 2.f;
		wz = m_w * m_v.z * 2.f;

		result[0][0] = 1.0f - (yy + zz);
		result[0][1] = xy - wz;
		result[0][2] = xz + wy;
		result[0][3] = 0;

		result[1][0] = xy + wz;
		result[1][1] = 1.0f - (xx + zz);
		result[1][2] = yz - wx;
		result[1][3] = 0;

		result[2][0] = xz - wy;
		result[2][1] = yz + wx;
		result[2][2] = 1.0f - (xx + yy);
		result[2][3] = 0;

		result[3][0] = 0;
		result[3][1] = 0;
		result[3][2] = 0;
		result[3][3] = 1;
	}

	r_inline CMat4 CQuat::ToMatrix (void) const {
		CMat4 result;
		this->ToMatrix(result);
		return result;
	}

	r_inline void CQuat::Identity(void){
		m_v.Set(0,0,0);
		m_w = 1.0f;
	}

}

#endif
