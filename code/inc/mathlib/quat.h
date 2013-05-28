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

#ifndef __QUAT_H__
#define __QUAT_H__

namespace rengine3d {

	//!  ласс дл€ работы с  ватернионами (четырехмерное комплексное число, используемое дл€ представлени€ вращени€ в трехмерном пространстве)
	//! ќдним из наиболее полезных свойств кватернионов €вл€етс€ достижение гладкой анимации при интерпол€ции

	class CQuat {
	public:
		CQuat() {}
		CQuat(float w_, float x_, float y_, float z_);
		CQuat(float headDegrees, float pitchDegrees, float rollDegrees);
		CQuat(const CVec3 &axis, float degrees);

		~CQuat() {}

		CQuat &operator+=(const CQuat &rhs);
		CQuat &operator-=(const CQuat &rhs);
		CQuat &operator*=(const CQuat &rhs);
		CQuat &operator*=(float scalar);
		CQuat &operator/=(float scalar);

		CQuat operator+(const CQuat &rhs) const;
		CQuat operator-(const CQuat &rhs) const;
		CQuat operator*(const CQuat &rhs) const;
		CQuat operator*(float scalar) const;
		CQuat operator/(float scalar) const;

		void Identity();

		CQuat Slerp(const CQuat& a, const CQuat& b, float t);

		void FromAxisAngle(const CVec3 &axis, float degrees);
		void FromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
		void FromMatrix(const CMat4 &m);
		CMat4 ToMatrix4() const;

	public:
		float w, x, y, z;
	};

	r_inline CQuat operator*(float lhs, const CQuat &rhs) {
		return rhs * lhs;
	}

	r_inline CQuat::CQuat(float w_, float x_, float y_, float z_)
		: w(w_), x(x_), y(y_), z(z_) {}

	r_inline CQuat::CQuat(float headDegrees, float pitchDegrees, float rollDegrees)	{
		FromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
	}

	r_inline CQuat::CQuat(const CVec3 &axis, float degrees) {
		FromAxisAngle(axis, degrees);
	}

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

	r_inline CQuat &CQuat::operator*=(float scalar){
		w *= scalar, x *= scalar, y *= scalar, z *= scalar;
		return *this;
	}

	r_inline CQuat &CQuat::operator/=(float scalar)	{
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

	r_inline CQuat CQuat::operator*(float scalar) const {
		CQuat tmp(*this);
		tmp *= scalar;
		return tmp;
	}

	r_inline CQuat CQuat::operator/(float scalar) const {
		CQuat tmp(*this);
		tmp /= scalar;
		return tmp;
	}

	r_inline void CQuat::Identity(){
		w = 1.0f, x = y = z = 0.0f;
	}

	r_inline CQuat CQuat::Slerp(const CQuat& a, const CQuat& b, float t) {
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
		float omega = 0.0f;
		float cosom = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		float sinom = 0.0f;
		float scale0 = 0.0f;
		float scale1 = 0.0f;

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

	r_inline void CQuat::FromAxisAngle(const CVec3 &axis, float degrees) {
		float halfTheta = DegreesToRadians(degrees) * 0.5f;
		float s = sinf(halfTheta);
		w = cosf(halfTheta), x = axis.x * s, y = axis.y * s, z = axis.z * s;
	}

	r_inline void CQuat::FromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees) {
	}

	r_inline void CQuat::FromMatrix(const CMat4 &m) {
		// Creates a quaternion from a rotation matrix. 
		// The algorithm used is from Allan and Mark Watt's "Advanced 
		// Animation and Rendering Techniques" (ACM Press 1992).

		float s = 0.0f;
		float q[4] = {0.0f};
		float trace = m[0][0] + m[1][1] + m[2][2];

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

		float x2 = x + x; 
		float y2 = y + y; 
		float z2 = z + z;
		float xx = x * x2;
		float xy = x * y2;
		float xz = x * z2;
		float yy = y * y2;
		float yz = y * z2;
		float zz = z * z2;
		float wx = w * x2;
		float wy = w * y2;
		float wz = w * z2;

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

}

#endif
