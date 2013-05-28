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

#ifndef __MAT4_H__
#define __MAT4_H__

namespace rengine3d {

	class CMat4 {
		friend CVec3 operator*(const CVec3 &lhs, const CMat4 &rhs);
		friend CMat4 operator*(float scalar, const CMat4 &rhs);

	public:
		CMat4() {}
		CMat4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);
		~CMat4() {}

		float *operator[](int row);
		const float *operator[](int row) const;

		bool operator==(const CMat4 &rhs) const;		
		bool operator!=(const CMat4 &rhs) const;

		CMat4 &operator+=(const CMat4 &rhs);
		CMat4 &operator-=(const CMat4 &rhs);
		CMat4 &operator*=(const CMat4 &rhs);
		CMat4 &operator*=(float scalar);
		CMat4 &operator/=(float scalar);

		CMat4 operator+(const CMat4 &rhs) const;
		CMat4 operator-(const CMat4 &rhs) const;
		CMat4 operator*(const CMat4 &rhs) const;
		CMat4 operator*(float scalar) const;
		CMat4 operator/(float scalar) const;

		void Identity();
		void Perspective(real fov, real aspect, real znear, real zfar);
		void Rotate(const CVec3& axis, float degrees);
		void Scale(float sx, float sy, float sz);
		void Translate(float tx, float ty, float tz);

		CVec3 GetForward(void) const;
		CVec3 GetRight(void) const;
		CVec3 GetUp(void) const;

		const float *ToFloatPtr( void ) const;

	private:
		float m[4][4];
	};

	r_inline CVec3 operator*(const CVec3 &lhs, const CMat4 &rhs) {
		return CVec3((lhs.x * rhs[0][0]) + (lhs.y * rhs[1][0]) + (lhs.z * rhs[2][0]),
			(lhs.x * rhs[0][1]) + (lhs.y * rhs[1][1]) + (lhs.z * rhs[2][1]),
			(lhs.x * rhs[0][2]) + (lhs.y * rhs[1][2]) + (lhs.z * rhs[2][2]));
	}

	r_inline CMat4 operator*(float scalar, const CMat4 &rhs) {
		return rhs * scalar;
	}

	r_inline CMat4::CMat4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44)	{
			m[0][0] = m11, m[0][1] = m12, m[0][2] = m13, m[0][3] = m14;
			m[1][0] = m21, m[1][1] = m22, m[1][2] = m23, m[1][3] = m24;
			m[2][0] = m31, m[2][1] = m32, m[2][2] = m33, m[2][3] = m34;
			m[3][0] = m41, m[3][1] = m42, m[3][2] = m43, m[3][3] = m44;
	}

	r_inline float *CMat4::operator[](int row){
		return m[row];
	}

	r_inline const float *CMat4::operator[](int row) const {
		return m[row];
	}

	r_inline bool CMat4::operator==(const CMat4 &rhs) const	{
		return CloseEnough(m[0][0], rhs.m[0][0])
			&& CloseEnough(m[0][1], rhs.m[0][1])
			&& CloseEnough(m[0][2], rhs.m[0][2])
			&& CloseEnough(m[0][3], rhs.m[0][3])
			&& CloseEnough(m[1][0], rhs.m[1][0])
			&& CloseEnough(m[1][1], rhs.m[1][1])
			&& CloseEnough(m[1][2], rhs.m[1][2])
			&& CloseEnough(m[1][3], rhs.m[1][3])
			&& CloseEnough(m[2][0], rhs.m[2][0])
			&& CloseEnough(m[2][1], rhs.m[2][1])
			&& CloseEnough(m[2][2], rhs.m[2][2])
			&& CloseEnough(m[2][3], rhs.m[2][3])
			&& CloseEnough(m[3][0], rhs.m[3][0])
			&& CloseEnough(m[3][1], rhs.m[3][1])
			&& CloseEnough(m[3][2], rhs.m[3][2])
			&& CloseEnough(m[3][3], rhs.m[3][3]);
	}

	r_inline bool CMat4::operator!=(const CMat4 &rhs) const	{
		return !(*this == rhs);
	}

	r_inline CMat4 &CMat4::operator+=(const CMat4 &rhs) {
		m[0][0] += rhs.m[0][0], m[0][1] += rhs.m[0][1], m[0][2] += rhs.m[0][2], m[0][3] += rhs.m[0][3];
		m[1][0] += rhs.m[1][0], m[1][1] += rhs.m[1][1], m[1][2] += rhs.m[1][2], m[1][3] += rhs.m[1][3];
		m[2][0] += rhs.m[2][0], m[2][1] += rhs.m[2][1], m[2][2] += rhs.m[2][2], m[2][3] += rhs.m[2][3];
		m[3][0] += rhs.m[3][0], m[3][1] += rhs.m[3][1], m[3][2] += rhs.m[3][2], m[3][3] += rhs.m[3][3];
		return *this;
	}

	r_inline CMat4 &CMat4::operator-=(const CMat4 &rhs)	{
		m[0][0] -= rhs.m[0][0], m[0][1] -= rhs.m[0][1], m[0][2] -= rhs.m[0][2], m[0][3] -= rhs.m[0][3];
		m[1][0] -= rhs.m[1][0], m[1][1] -= rhs.m[1][1], m[1][2] -= rhs.m[1][2], m[1][3] -= rhs.m[1][3];
		m[2][0] -= rhs.m[2][0], m[2][1] -= rhs.m[2][1], m[2][2] -= rhs.m[2][2], m[2][3] -= rhs.m[2][3];
		m[3][0] -= rhs.m[3][0], m[3][1] -= rhs.m[3][1], m[3][2] -= rhs.m[3][2], m[3][3] -= rhs.m[3][3];
		return *this;
	}

	r_inline CMat4 &CMat4::operator*=(const CMat4 &rhs)	{
		CMat4 tmp;

		// Row 1.
		tmp.m[0][0] = (m[0][0] * rhs.m[0][0]) + (m[0][1] * rhs.m[1][0]) + (m[0][2] * rhs.m[2][0]) + (m[0][3] * rhs.m[3][0]);
		tmp.m[0][1] = (m[0][0] * rhs.m[0][1]) + (m[0][1] * rhs.m[1][1]) + (m[0][2] * rhs.m[2][1]) + (m[0][3] * rhs.m[3][1]);
		tmp.m[0][2] = (m[0][0] * rhs.m[0][2]) + (m[0][1] * rhs.m[1][2]) + (m[0][2] * rhs.m[2][2]) + (m[0][3] * rhs.m[3][2]);
		tmp.m[0][3] = (m[0][0] * rhs.m[0][3]) + (m[0][1] * rhs.m[1][3]) + (m[0][2] * rhs.m[2][3]) + (m[0][3] * rhs.m[3][3]);

		// Row 2.
		tmp.m[1][0] = (m[1][0] * rhs.m[0][0]) + (m[1][1] * rhs.m[1][0]) + (m[1][2] * rhs.m[2][0]) + (m[1][3] * rhs.m[3][0]);
		tmp.m[1][1] = (m[1][0] * rhs.m[0][1]) + (m[1][1] * rhs.m[1][1]) + (m[1][2] * rhs.m[2][1]) + (m[1][3] * rhs.m[3][1]);
		tmp.m[1][2] = (m[1][0] * rhs.m[0][2]) + (m[1][1] * rhs.m[1][2]) + (m[1][2] * rhs.m[2][2]) + (m[1][3] * rhs.m[3][2]);
		tmp.m[1][3] = (m[1][0] * rhs.m[0][3]) + (m[1][1] * rhs.m[1][3]) + (m[1][2] * rhs.m[2][3]) + (m[1][3] * rhs.m[3][3]);

		// Row 3.
		tmp.m[2][0] = (m[2][0] * rhs.m[0][0]) + (m[2][1] * rhs.m[1][0]) + (m[2][2] * rhs.m[2][0]) + (m[2][3] * rhs.m[3][0]);
		tmp.m[2][1] = (m[2][0] * rhs.m[0][1]) + (m[2][1] * rhs.m[1][1]) + (m[2][2] * rhs.m[2][1]) + (m[2][3] * rhs.m[3][1]);
		tmp.m[2][2] = (m[2][0] * rhs.m[0][2]) + (m[2][1] * rhs.m[1][2]) + (m[2][2] * rhs.m[2][2]) + (m[2][3] * rhs.m[3][2]);
		tmp.m[2][3] = (m[2][0] * rhs.m[0][3]) + (m[2][1] * rhs.m[1][3]) + (m[2][2] * rhs.m[2][3]) + (m[2][3] * rhs.m[3][3]);

		// Row 4.
		tmp.m[3][0] = (m[3][0] * rhs.m[0][0]) + (m[3][1] * rhs.m[1][0]) + (m[3][2] * rhs.m[2][0]) + (m[3][3] * rhs.m[3][0]);
		tmp.m[3][1] = (m[3][0] * rhs.m[0][1]) + (m[3][1] * rhs.m[1][1]) + (m[3][2] * rhs.m[2][1]) + (m[3][3] * rhs.m[3][1]);
		tmp.m[3][2] = (m[3][0] * rhs.m[0][2]) + (m[3][1] * rhs.m[1][2]) + (m[3][2] * rhs.m[2][2]) + (m[3][3] * rhs.m[3][2]);
		tmp.m[3][3] = (m[3][0] * rhs.m[0][3]) + (m[3][1] * rhs.m[1][3]) + (m[3][2] * rhs.m[2][3]) + (m[3][3] * rhs.m[3][3]);

		*this = tmp;
		return *this;
	}

	r_inline CMat4 &CMat4::operator*=(float scalar)	{
		m[0][0] *= scalar, m[0][1] *= scalar, m[0][2] *= scalar, m[0][3] *= scalar;
		m[1][0] *= scalar, m[1][1] *= scalar, m[1][2] *= scalar, m[1][3] *= scalar;
		m[2][0] *= scalar, m[2][1] *= scalar, m[2][2] *= scalar, m[2][3] *= scalar;
		m[3][0] *= scalar, m[3][1] *= scalar, m[3][2] *= scalar, m[3][3] *= scalar;
		return *this;
	}

	r_inline CMat4 &CMat4::operator/=(float scalar)	{
		m[0][0] /= scalar, m[0][1] /= scalar, m[0][2] /= scalar, m[0][3] /= scalar;
		m[1][0] /= scalar, m[1][1] /= scalar, m[1][2] /= scalar, m[1][3] /= scalar;
		m[2][0] /= scalar, m[2][1] /= scalar, m[2][2] /= scalar, m[2][3] /= scalar;
		m[3][0] /= scalar, m[3][1] /= scalar, m[3][2] /= scalar, m[3][3] /= scalar;
		return *this;
	}

	r_inline CMat4 CMat4::operator+(const CMat4 &rhs) const	{
		CMat4 tmp(*this);
		tmp += rhs;
		return tmp;
	}

	r_inline CMat4 CMat4::operator-(const CMat4 &rhs) const	{
		CMat4 tmp(*this);
		tmp -= rhs;
		return tmp;
	}

	r_inline CMat4 CMat4::operator*(const CMat4 &rhs) const	{
		CMat4 tmp(*this);
		tmp *= rhs;
		return tmp;
	}

	r_inline CMat4 CMat4::operator*(float scalar) const	{
		CMat4 tmp(*this);
		tmp *= scalar;
		return tmp;
	}

	r_inline CMat4 CMat4::operator/(float scalar) const	{
		CMat4 tmp(*this);
		tmp /= scalar;
		return tmp;
	}

	r_inline void CMat4::Identity()	{
		m[0][0] = 1.0f, m[0][1] = 0.0f, m[0][2] = 0.0f, m[0][3] = 0.0f;
		m[1][0] = 0.0f, m[1][1] = 1.0f, m[1][2] = 0.0f, m[1][3] = 0.0f;
		m[2][0] = 0.0f, m[2][1] = 0.0f, m[2][2] = 1.0f, m[2][3] = 0.0f;
		m[3][0] = 0.0f, m[3][1] = 0.0f, m[3][2] = 0.0f, m[3][3] = 1.0f;
	}

	r_inline void CMat4::Perspective( real fov, real aspect, real znear, real zfar ) {
		float e = 1.0f / tanf((fov * DEG2RAD ) / 2.0f);
		float aspectInv = 1.0f / aspect;
		float fovy = 2.0f * atanf(aspectInv / e);
		float xScale = 1.0f / tanf(0.5f * fovy);
		float yScale = xScale / aspectInv;

		m[0][0] = xScale;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = yScale;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = (zfar + znear) / (znear - zfar);
		m[2][3] = -1.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = (2.0f * zfar * znear) / (znear - zfar);
		m[3][3] = 0.0f;

	}

	r_inline const float* CMat4::ToFloatPtr( void ) const {
		return m[0];
	}

	r_inline void CMat4::Rotate(const CVec3& axis, float degrees)	{
		// Creates a rotation matrix about the specified axis.
		// The axis must be a unit vector. The angle must be in degrees.
		//
		// Let u = axis of rotation = (x, y, z)
		//
		//             | x^2(1 - c) + c  xy(1 - c) + zs  xz(1 - c) - ys   0 |
		// Ru(angle) = | yx(1 - c) - zs  y^2(1 - c) + c  yz(1 - c) + xs   0 |
		//             | zx(1 - c) - ys  zy(1 - c) - xs  z^2(1 - c) + c   0 |
		//             |      0              0                0           1 |
		//
		// where,
		//	c = cos(angle)
		//  s = sin(angle)

		degrees = DegreesToRadians(degrees);

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;
		float c = cosf(degrees);
		float s = sinf(degrees);

		m[0][0] = (x * x) * (1.0f - c) + c;
		m[0][1] = (x * y) * (1.0f - c) + (z * s);
		m[0][2] = (x * z) * (1.0f - c) - (y * s);
		m[0][3] = 0.0f;

		m[1][0] = (y * x) * (1.0f - c) - (z * s);
		m[1][1] = (y * y) * (1.0f - c) + c;
		m[1][2] = (y * z) * (1.0f - c) + (x * s);
		m[1][3] = 0.0f;

		m[2][0] = (z * x) * (1.0f - c) + (y * s);
		m[2][1] = (z * y) * (1.0f - c) - (x * s);
		m[2][2] = (z * z) * (1.0f - c) + c;
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}


	r_inline void CMat4::Scale(float sx, float sy, float sz){
		// Creates a scaling matrix.
		//
		//                 | sx   0    0    0 |
		// S(sx, sy, sz) = | 0    sy   0    0 |
		//                 | 0    0    sz   0 |
		//                 | 0    0    0    1 |

		m[0][0] = sx,   m[0][1] = 0.0f, m[0][2] = 0.0f, m[0][3] = 0.0f;
		m[1][0] = 0.0f, m[1][1] = sy,   m[1][2] = 0.0f, m[1][3] = 0.0f;
		m[2][0] = 0.0f, m[2][1] = 0.0f, m[2][2] = sz,   m[2][3] = 0.0f;
		m[3][0] = 0.0f, m[3][1] = 0.0f, m[3][2] = 0.0f, m[3][3] = 1.0f;
	}

	r_inline void CMat4::Translate(float tx, float ty, float tz) {
		// Creates a translation matrix.
		//
		//                 | 1    0    0    0 |
		// T(tx, ty, tz) = | 0    1    0    0 |
		//                 | 0    0    1    0 |
		//                 | tx   ty   tz   1 |

		m[0][0] = 1.0f, m[0][1] = 0.0f, m[0][2] = 0.0f, m[0][3] = 0.0f;
		m[1][0] = 0.0f, m[1][1] = 1.0f, m[1][2] = 0.0f, m[1][3] = 0.0f;
		m[2][0] = 0.0f, m[2][1] = 0.0f, m[2][2] = 1.0f, m[2][3] = 0.0f;
		m[3][0] = tx,   m[3][1] = ty,   m[3][2] = tz,   m[3][3] = 1.0f;
	}

	r_inline CVec3 CMat4::GetForward(void) const {
		return CVec3(m[2][0], m[2][1], m[2][2]);
	}

	r_inline CVec3 CMat4::GetRight(void) const {
		return CVec3(m[0][0], m[0][1], m[0][2]);
	}

	r_inline CVec3 CMat4::GetUp(void) const {
		return CVec3(m[1][0], m[1][1], m[1][2]);
	}

}

#endif
