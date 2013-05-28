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

#ifndef __VEC4_H__
#define __VEC4_H__

namespace rengine3d {

	//! 4D вектор
	class CVec4 {
	public:
		// Конструкторы
		CVec4(): x(0.0f), y(0.0f), z(0.0f), w(1) {}
		CVec4( real x, real y, real z, real w): x(x), y(y), z(z), w(w) {}
		CVec4( const CVec4& vec ): x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}

		// Операторы
		const CVec4 operator*( real f ) const			{ return CVec4( x * f, y * f, z * f, w * f ); }
		const CVec4 operator/( real f ) const			{ return CVec4( x / f, y / f, z / f, w / f ); }
		const CVec4 operator+( const CVec4& v ) const	{ return CVec4( x + v.x, y + v.y, z + v.z, w + v.w ); }
		const CVec4 operator-() const					{ return CVec4( -x, -y, -z, -w ); }
		const CVec4 operator-( const CVec4& v ) const	{ return CVec4( x - v.x, y - v.y, z - v.z, w - v.w ); }

		CVec4 &operator*=( real f)				{ return *this = *this * f; }
		CVec4 &operator/=( real f)				{ return *this = *this / f; }
		CVec4 &operator+=( const CVec4& v )		{ return *this = *this + v; }
		CVec4 &operator-=( const CVec4& v )		{ return *this = *this - v; }

		real operator*(const CVec4 &v) const	{ return x * v.x + y * v.y + z * v.z + w * v.w; }

		operator real*()						{ return (real*)&x; }
		operator const real*() const			{ return (real*)&x; }

		real &operator[](int i)					{ return ((real*)&x)[i]; }
		const real operator[](int i) const		{ return ((real*)&x)[i]; }

		//! Установить по компонентам 
		void Set( real _x, real _y, real _z, real _w );

		//! Установить по входящему вектору 
		void Set( const CVec4& vec );

	public:
		real x,y,z,w;
	};

	r_inline void CVec4::Set( real _x, real _y, real _z, real _w ) {
		this->x = _x; this->y = _y; this->z = _z; this->w = _w;
	}

	r_inline void CVec4::Set( const CVec4& vec ) {
		this->x = vec.x; this->y = vec.y; this->z = vec.z; this->w = vec.w;
	}

}
#endif
