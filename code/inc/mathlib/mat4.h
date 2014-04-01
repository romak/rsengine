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

#ifndef __MAT4_H__
#define __MAT4_H__

namespace rengine3d {

	class CMat4 {
		friend CVec3 operator*(const CVec3 &lhs, const CMat4 &rhs);
		friend CMat4 operator*(real scalar, const CMat4 &rhs);

	public:
		CMat4() { this->Identity();}
		CMat4(real m11, real m12, real m13, real m14,
			real m21, real m22, real m23, real m24,
			real m31, real m32, real m33, real m34,
			real m41, real m42, real m43, real m44);
		~CMat4() {}

		real *operator[](int row);
		const real *operator[](int row) const;

		bool operator==(const CMat4 &rhs) const;		
		bool operator!=(const CMat4 &rhs) const;

		CMat4 &operator+=(const CMat4 &rhs);
		CMat4 &operator-=(const CMat4 &rhs);
		CMat4 &operator*=(const CMat4 &rhs);
		CMat4 &operator*=(real scalar);
		CMat4 &operator/=(real scalar);

		CMat4 operator+(const CMat4 &rhs) const;
		CMat4 operator-(const CMat4 &rhs) const;
		CMat4 operator*(const CMat4 &rhs) const;
		CMat4 operator*(real scalar) const;
		CMat4 operator/(real scalar) const;

		void Set(real n11, real n12, real n13, real n14, real n21, real n22, real n23, real n24, real n31, real n32, real n33, real n34, real n41, real n42, real n43, real n44);

		real Determinant(void) const;
		void Decompose(CVec3& pos, CVec3& rot, CVec3& scale) const;
		void Compose(CVec3& pos, CVec3& rot, CVec3& scale);

		void Identity();
		void Perspective(real fov, real aspect, real znear, real zfar);
		void Rotate(const CVec3& axis, real degrees);
		void Scale(real sx, real sy, real sz);
		void Translate(real tx, real ty, real tz);

		CMat4 MakeRotationFromQuaternion(real x, real y, real z, real w);

		CVec3 GetForward(void) const;
		CVec3 GetRight(void) const;
		CVec3 GetUp(void) const;

		CMat4 GetInverse(void);

		const real *TorealPtr( void ) const;

	private:
		union {
			real m[4][4];
			real m_elements[16];
		};
	};

	r_inline CVec3 operator*(const CVec3 &lhs, const CMat4 &rhs) {
		return CVec3((lhs.x * rhs[0][0]) + (lhs.y * rhs[1][0]) + (lhs.z * rhs[2][0]),
			(lhs.x * rhs[0][1]) + (lhs.y * rhs[1][1]) + (lhs.z * rhs[2][1]),
			(lhs.x * rhs[0][2]) + (lhs.y * rhs[1][2]) + (lhs.z * rhs[2][2]));
	}

	r_inline CMat4 operator*(real scalar, const CMat4 &rhs) {
		return rhs * scalar;
	}

	r_inline CMat4::CMat4(real m11, real m12, real m13, real m14,
		real m21, real m22, real m23, real m24,
		real m31, real m32, real m33, real m34,
		real m41, real m42, real m43, real m44)	{
			m[0][0] = m11, m[0][1] = m12, m[0][2] = m13, m[0][3] = m14;
			m[1][0] = m21, m[1][1] = m22, m[1][2] = m23, m[1][3] = m24;
			m[2][0] = m31, m[2][1] = m32, m[2][2] = m33, m[2][3] = m34;
			m[3][0] = m41, m[3][1] = m42, m[3][2] = m43, m[3][3] = m44;
	}

	r_inline real* CMat4::operator[](int row){
		return m[row];
	}

	r_inline const real *CMat4::operator[](int row) const {
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

	r_inline CMat4 &CMat4::operator*=(real scalar)	{
		m[0][0] *= scalar, m[0][1] *= scalar, m[0][2] *= scalar, m[0][3] *= scalar;
		m[1][0] *= scalar, m[1][1] *= scalar, m[1][2] *= scalar, m[1][3] *= scalar;
		m[2][0] *= scalar, m[2][1] *= scalar, m[2][2] *= scalar, m[2][3] *= scalar;
		m[3][0] *= scalar, m[3][1] *= scalar, m[3][2] *= scalar, m[3][3] *= scalar;
		return *this;
	}

	r_inline CMat4 &CMat4::operator/=(real scalar)	{
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

	r_inline CMat4 CMat4::operator*(real scalar) const	{
		CMat4 tmp(*this);
		tmp *= scalar;
		return tmp;
	}

	r_inline CMat4 CMat4::operator/(real scalar) const	{
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
		real e = 1.0f / tanf((fov * DEG2RAD ) / 2.0f);
		real aspectInv = 1.0f / aspect;
		real fovy = 2.0f * atanf(aspectInv / e);
		real xScale = 1.0f / tanf(0.5f * fovy);
		real yScale = xScale / aspectInv;

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

	r_inline const real* CMat4::TorealPtr( void ) const {
		return m[0];
	}

	r_inline void CMat4::Rotate(const CVec3& axis, real degrees)	{
		degrees = DegreesToRadians(degrees);

		real x = axis.x;
		real y = axis.y;
		real z = axis.z;
		real c = cosf(degrees);
		real s = sinf(degrees);

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

	r_inline void CMat4::Scale(real sx, real sy, real sz){
		m[0][0] = sx;
		m[1][1] = sy;
		m[2][2] = sz;
	}

	r_inline void CMat4::Translate(real tx, real ty, real tz) {
		m[3][0] = tx;
		m[3][1] = ty;
		m[3][2] = tz;
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

	r_inline CMat4 CMat4::GetInverse(void) {
		CMat4 mat;

		real d = this->Determinant();
		if( d == 0 ) return mat;
		d = 1.0f / d;

		m[0][0] = d * (m[1][2]*m[2][3]*m[3][1] - m[1][3]*m[2][2]*m[3][1] + m[1][3]*m[2][1]*m[3][2] - m[1][1]*m[2][3]*m[3][2] - m[1][2]*m[2][1]*m[3][3] + m[1][1]*m[2][2]*m[3][3]);
		m[0][1] = d * (m[0][3]*m[2][2]*m[3][1] - m[0][2]*m[2][3]*m[3][1] - m[0][3]*m[2][1]*m[3][2] + m[0][1]*m[2][3]*m[3][2] + m[0][2]*m[2][1]*m[3][3] - m[0][1]*m[2][2]*m[3][3]);
		m[0][2] = d * (m[0][2]*m[1][3]*m[3][1] - m[0][3]*m[1][2]*m[3][1] + m[0][3]*m[1][1]*m[3][2] - m[0][1]*m[1][3]*m[3][2] - m[0][2]*m[1][1]*m[3][3] + m[0][1]*m[1][2]*m[3][3]);
		m[0][3] = d * (m[0][3]*m[1][2]*m[2][1] - m[0][2]*m[1][3]*m[2][1] - m[0][3]*m[1][1]*m[2][2] + m[0][1]*m[1][3]*m[2][2] + m[0][2]*m[1][1]*m[2][3] - m[0][1]*m[1][2]*m[2][3]);
		m[1][0] = d * (m[1][3]*m[2][2]*m[3][0] - m[1][2]*m[2][3]*m[3][0] - m[1][3]*m[2][0]*m[3][2] + m[1][0]*m[2][3]*m[3][2] + m[1][2]*m[2][0]*m[3][3] - m[1][0]*m[2][2]*m[3][3]);
		m[1][1] = d * (m[0][2]*m[2][3]*m[3][0] - m[0][3]*m[2][2]*m[3][0] + m[0][3]*m[2][0]*m[3][2] - m[0][0]*m[2][3]*m[3][2] - m[0][2]*m[2][0]*m[3][3] + m[0][0]*m[2][2]*m[3][3]);
		m[1][2] = d * (m[0][3]*m[1][2]*m[3][0] - m[0][2]*m[1][3]*m[3][0] - m[0][3]*m[1][0]*m[3][2] + m[0][0]*m[1][3]*m[3][2] + m[0][2]*m[1][0]*m[3][3] - m[0][0]*m[1][2]*m[3][3]);
		m[1][3] = d * (m[0][2]*m[1][3]*m[2][0] - m[0][3]*m[1][2]*m[2][0] + m[0][3]*m[1][0]*m[2][2] - m[0][0]*m[1][3]*m[2][2] - m[0][2]*m[1][0]*m[2][3] + m[0][0]*m[1][2]*m[2][3]);
		m[2][0] = d * (m[1][1]*m[2][3]*m[3][0] - m[1][3]*m[2][1]*m[3][0] + m[1][3]*m[2][0]*m[3][1] - m[1][0]*m[2][3]*m[3][1] - m[1][1]*m[2][0]*m[3][3] + m[1][0]*m[2][1]*m[3][3]);
		m[2][1] = d * (m[0][3]*m[2][1]*m[3][0] - m[0][1]*m[2][3]*m[3][0] - m[0][3]*m[2][0]*m[3][1] + m[0][0]*m[2][3]*m[3][1] + m[0][1]*m[2][0]*m[3][3] - m[0][0]*m[2][1]*m[3][3]);
		m[2][2] = d * (m[0][1]*m[1][3]*m[3][0] - m[0][3]*m[1][1]*m[3][0] + m[0][3]*m[1][0]*m[3][1] - m[0][0]*m[1][3]*m[3][1] - m[0][1]*m[1][0]*m[3][3] + m[0][0]*m[1][1]*m[3][3]);
		m[2][3] = d * (m[0][3]*m[1][1]*m[2][0] - m[0][1]*m[1][3]*m[2][0] - m[0][3]*m[1][0]*m[2][1] + m[0][0]*m[1][3]*m[2][1] + m[0][1]*m[1][0]*m[2][3] - m[0][0]*m[1][1]*m[2][3]);
		m[3][0] = d * (m[1][2]*m[2][1]*m[3][0] - m[1][1]*m[2][2]*m[3][0] - m[1][2]*m[2][0]*m[3][1] + m[1][0]*m[2][2]*m[3][1] + m[1][1]*m[2][0]*m[3][2] - m[1][0]*m[2][1]*m[3][2]);
		m[3][1] = d * (m[0][1]*m[2][2]*m[3][0] - m[0][2]*m[2][1]*m[3][0] + m[0][2]*m[2][0]*m[3][1] - m[0][0]*m[2][2]*m[3][1] - m[0][1]*m[2][0]*m[3][2] + m[0][0]*m[2][1]*m[3][2]);
		m[3][2] = d * (m[0][2]*m[1][1]*m[3][0] - m[0][1]*m[1][2]*m[3][0] - m[0][2]*m[1][0]*m[3][1] + m[0][0]*m[1][2]*m[3][1] + m[0][1]*m[1][0]*m[3][2] - m[0][0]*m[1][1]*m[3][2]);
		m[3][3] = d * (m[0][1]*m[1][2]*m[2][0] - m[0][2]*m[1][1]*m[2][0] + m[0][2]*m[1][0]*m[2][1] - m[0][0]*m[1][2]*m[2][1] - m[0][1]*m[1][0]*m[2][2] + m[0][0]*m[1][1]*m[2][2]);

		return mat;
	}

	r_inline real CMat4::Determinant(void) const {
		return 
			m[0][3]*m[1][2]*m[2][1]*m[3][0] - m[0][2]*m[1][3]*m[2][1]*m[3][0] - m[0][3]*m[1][1]*m[2][2]*m[3][0] + m[0][1]*m[1][3]*m[2][2]*m[3][0] +
			m[0][2]*m[1][1]*m[2][3]*m[3][0] - m[0][1]*m[1][2]*m[2][3]*m[3][0] - m[0][3]*m[1][2]*m[2][0]*m[3][1] + m[0][2]*m[1][3]*m[2][0]*m[3][1] +
			m[0][3]*m[1][0]*m[2][2]*m[3][1] - m[0][0]*m[1][3]*m[2][2]*m[3][1] - m[0][2]*m[1][0]*m[2][3]*m[3][1] + m[0][0]*m[1][2]*m[2][3]*m[3][1] +
			m[0][3]*m[1][1]*m[2][0]*m[3][2] - m[0][1]*m[1][3]*m[2][0]*m[3][2] - m[0][3]*m[1][0]*m[2][1]*m[3][2] + m[0][0]*m[1][3]*m[2][1]*m[3][2] +
			m[0][1]*m[1][0]*m[2][3]*m[3][2] - m[0][0]*m[1][1]*m[2][3]*m[3][2] - m[0][2]*m[1][1]*m[2][0]*m[3][3] + m[0][1]*m[1][2]*m[2][0]*m[3][3] +
			m[0][2]*m[1][0]*m[2][1]*m[3][3] - m[0][0]*m[1][2]*m[2][1]*m[3][3] - m[0][1]*m[1][0]*m[2][2]*m[3][3] + m[0][0]*m[1][1]*m[2][2]*m[3][3];
	}

	r_inline void CMat4::Compose(CVec3& pos, CVec3& rot, CVec3& scale) {
		//this->MakeRotationFromQuaternion( quat );
	}

	r_inline void CMat4::Decompose( CVec3& pos, CVec3& rot, CVec3& scale ) const {
		pos = CVec3( m[3][0], m[3][1], m[3][2] );

		// Scale is length of columns
		scale.x = sqrtf( m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2] );
		scale.y = sqrtf( m[1][0] * m[1][0] + m[1][1] * m[1][1] + m[1][2] * m[1][2] );
		scale.z = sqrtf( m[2][0] * m[2][0] + m[2][1] * m[2][1] + m[2][2] * m[2][2] );

		if( scale.x == 0 || scale.y == 0 || scale.z == 0 ) return;

		// Detect negative scale with determinant and flip one arbitrary axis
		if( Determinant() < 0 ) scale.x = -scale.x;

		rot.x = asinf( -m[2][1] / scale.z );

		// Special case: Cos[x] == 0 (when Sin[x] is +/-1)
		real f = fabsf( m[2][1] / scale.z );
		if( f > 0.999f && f < 1.001f )
		{
			// Pin arbitrarily one of y or z to zero
			// Mathematical equivalent of gimbal lock
			rot.y = 0;

			// Now: Cos[x] = 0, Sin[x] = +/-1, Cos[y] = 1, Sin[y] = 0
			// => m[0][0] = Cos[z] and m[1][0] = Sin[z]
			rot.z = atan2f( -m[1][0] / scale.y, m[0][0] / scale.x );
		}
		// Standard case
		else
		{
			rot.y = atan2f( m[2][0] / scale.z, m[2][2] / scale.z );
			rot.z = atan2f( m[0][1] / scale.x, m[1][1] / scale.y );
		}

	}

	r_inline CMat4 CMat4::MakeRotationFromQuaternion(real x, real y, real z, real w) {
		CMat4 r;

		r[0][0] = 1.0f - (y*y*2 + z*z*2);
		r[1][0] = x*y*2 - w*z*2;
		r[2][0] = x*z*2 + w*y*2;
		r[3][0] = 0;

		r[0][1] = x*y*2 + w*z*2;
		r[1][1] = 1.0f - (x*x*2 + z*z*2);
		r[2][1] = y*z*2 - w*x*2;
		r[3][1] = 0;

		r[0][2] = x*z*2 - w*y*2;
		r[1][2] = y*z*2 + w*x*2;
		r[2][2] = 1.0f - (x*x*2 + y*y*2);
		r[3][2] = 0;

		r[0][3] = 0;
		r[1][3] = 0;
		r[2][3] = 0;
		r[3][3] = 1;

		return r;
	}

	r_inline void CMat4::Set(real n11, real n12, real n13, real n14, real n21, real n22, real n23, real n24, real n31, real n32, real n33, real n34, real n41, real n42, real n43, real n44) {
		m_elements[0] = n11; m_elements[4] = n12; m_elements[8] = n13; m_elements[12] = n14;
		m_elements[1] = n21; m_elements[5] = n22; m_elements[9] = n23; m_elements[13] = n24;
		m_elements[2] = n31; m_elements[6] = n32; m_elements[10] = n33; m_elements[14] = n34;
		m_elements[3] = n41; m_elements[7] = n42; m_elements[11] = n43; m_elements[15] = n44;
	}

}

#endif
