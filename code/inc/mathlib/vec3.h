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

#ifndef __VEC3_H__
#define __VEC3_H__

namespace rengine3d {

//#include "mathlib\quat.h"
	//class CQuat;

	//! 3D вектор
	class CVec3 {
	public:
		// Конструкторы
		CVec3(): x(0.0f), y(0.0f), z(0.0f) {}
		CVec3( real x, real y, real z ): x(x), y(y),z(z) {}
		CVec3( const CVec3& vec ): x(vec.x), y(vec.y), z(vec.z) {}

		CVec3 operator*( real f ) const	{ return CVec3( x * f, y * f, z * f ); }
		const CVec3 operator/( real f ) const	{ return CVec3( x / f, y / f, z / f ); }
		const CVec3 operator+( const CVec3& v ) const { return CVec3( x + v.x, y + v.y, z + v.z ); }
		const CVec3 operator-() const			{ return CVec3( -x, -y, -z ); }
		const CVec3 operator-( const CVec3& v ) const { return CVec3( x - v.x, y - v.y, z - v.z ); }

		CVec3 &operator*=( real f)				{ return *this = *this * f; }
		CVec3 &operator/=( real f)				{ return *this = *this / f; }
		CVec3 &operator+=( const CVec3& v )		{ return *this = *this + v; }
		CVec3 &operator-=( const CVec3& v )		{ return *this = *this - v; }

		CVec3 operator/(const CVec3& v) const;
		CVec3 operator*(const CVec3& v) const;

		bool operator==( const CVec3& v ) const { return Compare( v ); }
		bool operator!=( const CVec3& v ) const { return !Compare( v ); }

		operator real*()						{ return (real*)&x; }
		operator const real*() const			{ return (real*)&x; }

		real &operator[](int i)					{ return ((real*)&x)[i]; }
		const real operator[](int i) const		{ return ((real*)&x)[i]; }

		//! Сравнение с вектором
		bool Compare( const CVec3 &a ) const {return ( ( x == a.x ) && ( y == a.y ) && ( z == a.z ) ); }

		CVec3 Inverse() const;

		//! Установить по компонентам 
		void Set( real _x, real _y, real _z );

		//! Установить по входящему вектору 
		void Set( const CVec3& vec );

		//! Векторное произведение
		void Cross( const CVec3 &v1, const CVec3 &v2 );

		//! Векторное произведение
		CVec3 Cross( const CVec3& vec ) const;

		//! Приводит вектор к единичному виду
		real Normalize();

		//! Скалярное произведение
		real Dot( const CVec3& vec ) const { return (x * vec.x + y * vec.y + z * vec.z); };

		//! Длина вектора
		real Len( void ) const { return sqrt( x*x + y*y + z*z ); }

		real MagSq(void) const { return (x * x) + (y * y) + (z * z); };

		void Scale( const CVec3& vec, float scale );
		CVec3 Scale( float scale );

//		void ApplyQuaternion(CQuat q){};

	public:
		real x,y,z;
	};

	r_inline CVec3 CVec3::operator/(const CVec3& v) const {
		CVec3 vec;
		vec.x = x / v.x;
		vec.y = y / v.y;
		vec.z = z / v.z;
		return vec;
	}

	r_inline CVec3 CVec3::operator*(const CVec3& v) const {
		CVec3 vec;
		vec.x = x * v.x;
		vec.y = y * v.y;
		vec.z = z * v.z;
		return vec;
	}

	r_inline void CVec3::Set( real _x, real _y, real _z ) {
		this->x = _x; this->y = _y; this->z = _z;
	}

	r_inline void CVec3::Set( const CVec3& vec ) {
		this->x = vec.x; this->y = vec.y; this->z = vec.z;
	}

	r_inline CVec3 CVec3::Inverse() const {
		return CVec3(-x, -y, -z);
	}

	r_inline void CVec3::Cross( const CVec3 &v1,const CVec3 &v2 ) {
		x = v1.y * v2.z - v1.z * v2.y;
		y = v1.z * v2.x - v1.x * v2.z;
		z = v1.x * v2.y - v1.y * v2.x;
	}

	r_inline CVec3 CVec3::Cross( const CVec3& vec ) const {
		CVec3 res;

		res.x = (y * vec.z) - (z * vec.y);
		res.y = (z * vec.x) - (x * vec.z);
		res.z = (x * vec.y) - (y * vec.x);

		return res;
	}

	r_inline real CVec3::Normalize() {
		real inv,len = sqrt( x * x + y * y + z * z );

		if ( len < EPSILON ) 
			return 0.0;

		inv = 1.0f / len;
		x *= inv;
		y *= inv;
		z *= inv;

		return len;
	}

	r_inline void CVec3::Scale( const CVec3& vec, float scale ) {
		this->x = vec.x * scale;
		this->y = vec.y * scale;
		this->z = vec.z * scale;
	}

	r_inline CVec3 CVec3::Scale( float scale ) {
		return CVec3(this->x * scale, this->y * scale, this->z * scale );
	}
/*
	r_inline void CVec3::ApplyQuaternion(CQuat quat) {
	}
*/
}
#endif