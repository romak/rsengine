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

	//!  ласс дл€ работы с  ватернионами (четырехмерное комплексное число, используемое дл€ представлени€ вращени€ в трехмерном пространстве)
	//! ќдним из наиболее полезных свойств кватернионов €вл€етс€ достижение гладкой анимации при интерпол€ции

	class CVec3;
	class CVec4;
	class CMat4;

	class CQuat {
	public:
		CQuat(){};
	};

/*
	class CQuat {
	public:
		CQuat() {}
		CQuat(real w_, real x_, real y_, real z_);
		CQuat(real headDegrees, real pitchDegrees, real rollDegrees);
		//CQuat(const CVec3& axis, real degrees);

		~CQuat() {}

		CQuat &operator+=(const CQuat &rhs);
		CQuat &operator-=(const CQuat &rhs);
		CQuat &operator*=(const CQuat &rhs);
		CQuat &operator*=(real scalar);
		CQuat &operator/=(real scalar);

		CQuat operator+(const CQuat &rhs) const;
		CQuat operator-(const CQuat &rhs) const;
		CQuat operator*(const CQuat &rhs) const;
		CQuat operator*(real scalar) const;
		CQuat operator/(real scalar) const;

		void Identity();

		CQuat Slerp(const CQuat& a, const CQuat& b, real t);

//		void SetFromAxisAngle(CVec3 axis, real degrees);
		void FromHeadPitchRoll(real headDegrees, real pitchDegrees, real rollDegrees);
		void SetFromRotationMatrix(const CMat4 &m);
		CMat4 ToMatrix4() const;

	public:
		real w, x, y, z;
	};

	r_inline CQuat operator*(real lhs, const CQuat &rhs) {
		return rhs * lhs;
	}

	r_inline CQuat::CQuat(real w_, real x_, real y_, real z_)
		: w(w_), x(x_), y(y_), z(z_) {}

	r_inline CQuat::CQuat(real headDegrees, real pitchDegrees, real rollDegrees)	{
		FromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
	}

	//r_inline CQuat::CQuat(const CVec3 &axis, real degrees) {
	//	SetFromAxisAngle(axis, degrees);
	//}

	r_inline CQuat &CQuat::operator+=(const CQuat &rhs)	{
		w += rhs.w, x += rhs.x, y += rhs.y, z += rhs.z;
		return *this;
	}

	r_inline CQuat &CQuat::operator-=(const CQuat &rhs) {
		w -= rhs.w, x -= rhs.x, y -= rhs.y, z -= rhs.z;
		return *this;
	}

	r_inline CQuat &CQuat::operator*=(const CQuat &rhs)	{
		// Multiply so that rotations are applied in a left to right order.
		CQuat tmp(
			(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
			(w * rhs.x) + (x * rhs.w) - (y * rhs.z) + (z * rhs.y),
			(w * rhs.y) + (x * rhs.z) + (y * rhs.w) - (z * rhs.x),
			(w * rhs.z) - (x * rhs.y) + (y * rhs.x) + (z * rhs.w));

		*this = tmp;
		return *this;
	}

	r_inline CQuat &CQuat::operator*=(real scalar){
		w *= scalar, x *= scalar, y *= scalar, z *= scalar;
		return *this;
	}

	r_inline CQuat &CQuat::operator/=(real scalar)	{
		w /= scalar, x /= scalar, y /= scalar, z /= scalar;
		return *this;
	}

	r_inline CQuat CQuat::operator+(const CQuat &rhs) const {
		CQuat tmp(*this);
		tmp += rhs;
		return tmp;
	}

	r_inline CQuat CQuat::operator-(const CQuat &rhs) const {
		CQuat tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	r_inline CQuat CQuat::operator*(const CQuat &rhs) const {
		CQuat tmp(*this);
		tmp *= rhs;
		return tmp;
	}

	r_inline CQuat CQuat::operator*(real scalar) const {
		CQuat tmp(*this);
		tmp *= scalar;
		return tmp;
	}

	r_inline CQuat CQuat::operator/(real scalar) const {
		CQuat tmp(*this);
		tmp /= scalar;
		return tmp;
	}

	r_inline void CQuat::Identity(){
		w = 1.0f, x = y = z = 0.0f;
	}

	r_inline CQuat CQuat::Slerp(const CQuat& a, const CQuat& b, real t) {
		// Smoothly interpolates from quaternion 'a' to quaternion 'b' using
		// spherical linear interpolation.
		// 
		// Both quaternions must be unit length and represent absolute rotations.
		// In particular quaternion 'b' must not be relative to quaternion 'a'.
		// If 'b' is relative to 'a' make 'b' an absolute rotation by: b = a * b.
		// 
		// The interpolation parameter 't' is in the range [0,1]. When t = 0 the
		// resulting quaternion will be 'a'. When t = 1 the resulting quaternion
		// will be 'b'.
		//
		// The algorithm used is adapted from Allan and Mark Watt's "Advanced
		// Animation and Rendering Techniques" (ACM Press 1992).

		CQuat result;
		real omega = 0.0f;
		real cosom = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		real sinom = 0.0f;
		real scale0 = 0.0f;
		real scale1 = 0.0f;

		if ((1.0f + cosom) > EPSILON)
		{
			// 'a' and 'b' quaternions are not opposite each other.

			if ((1.0f - cosom) > EPSILON)
			{
				// Standard case - slerp.
				omega = acosf(cosom);
				sinom = sinf(omega);
				scale0 = sinf((1.0f - t) * omega) / sinom;
				scale1 = sinf(t * omega) / sinom;
			}
			else
			{
				// 'a' and 'b' quaternions are very close so lerp instead.
				scale0 = 1.0f - t;
				scale1 = t;
			}

			result.x = scale0 * a.x + scale1 * b.x;
			result.y = scale0 * a.y + scale1 * b.y;
			result.z = scale0 * a.z + scale1 * b.z;
			result.w = scale0 * a.w + scale1 * b.w;
		}
		else
		{
			// 'a' and 'b' quaternions are opposite each other.

			result.x = -b.y;
			result.y = b.x;
			result.z = -b.w;
			result.w = b.z;

			scale0 = sinf((1.0f - t) - HALF_PI);
			scale1 = sinf(t * HALF_PI);

			result.x = scale0 * a.x + scale1 * result.x;
			result.y = scale0 * a.y + scale1 * result.y;
			result.z = scale0 * a.z + scale1 * result.z;
			result.w = scale0 * a.w + scale1 * result.w;
		}

		return result;

	}

	r_inline void CQuat::SetFromAxisAngle(CVec3 axis, real degrees) {
		real halfTheta = DegreesToRadians(degrees) * 0.5f;
		real s = sinf(halfTheta);
		w = cosf(halfTheta), x = axis.x * s, y = axis.y * s, z = axis.z * s;
	}

	r_inline void CQuat::FromHeadPitchRoll(real headDegrees, real pitchDegrees, real rollDegrees) {
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

		x = q[0], y = q[1], z = q[2], w = q[3];
	}

	r_inline CMat4 CQuat::ToMatrix4() const {
		// Converts this quaternion to a rotation matrix.
		//
		//  | 1 - 2(y^2 + z^2)	2(xy + wz)			2(xz - wy)			0  |
		//  | 2(xy - wz)		1 - 2(x^2 + z^2)	2(yz + wx)			0  |
		//  | 2(xz + wy)		2(yz - wx)			1 - 2(x^2 + y^2)	0  |
		//  | 0					0					0					1  |

		real x2 = x + x; 
		real y2 = y + y; 
		real z2 = z + z;
		real xx = x * x2;
		real xy = x * y2;
		real xz = x * z2;
		real yy = y * y2;
		real yz = y * z2;
		real zz = z * z2;
		real wx = w * x2;
		real wy = w * y2;
		real wz = w * z2;

		CMat4 m;

		m[0][0] = 1.0f - (yy + zz);
		m[0][1] = xy + wz;
		m[0][2] = xz - wy;
		m[0][3] = 0.0f;

		m[1][0] = xy - wz;
		m[1][1] = 1.0f - (xx + zz);
		m[1][2] = yz + wx;
		m[1][3] = 0.0f;

		m[2][0] = xz + wy;
		m[2][1] = yz - wx;
		m[2][2] = 1.0f - (xx + yy);
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;

		return m;
	}
*/
}

#endif
