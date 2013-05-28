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

#ifndef __VEC2_H__
#define __VEC2_H__

namespace rengine3d {

	//! 2D вектор
	class CVec2 {
	public:
		// Конструкторы
		CVec2(): x(0.0f), y(0.0f) {}
		CVec2( real x, real y ): x(x), y(y) {}
		CVec2( const CVec2& vec ): x(vec.x), y(vec.y) {}

		// Операторы
		const CVec2 operator*( real f ) const	{ return CVec2(x * f, y * f); }
		const CVec2 operator/( real f ) const	{ return CVec2(x / f, y / f); }
		const CVec2 operator+( const CVec2& v ) const { return CVec2(x + v.x, y + v.y); }
		const CVec2 operator-() const			{ return CVec2(-x, -y); }
		const CVec2 operator-( const CVec2& v ) const { return CVec2(x - v.x ,y - v.y); }

		CVec2 &operator*=( real f)				{ return *this = *this * f; }
		CVec2 &operator/=( real f)				{ return *this = *this / f; }
		CVec2 &operator+=( const CVec2& v )		{ return *this = *this + v; }
		CVec2 &operator-=( const CVec2& v )		{ return *this = *this - v; }

		bool operator==( const CVec2& v ) const { return (v.x == x && v.y == y); }
		bool operator!=( const CVec2& v ) const { return (!(*this == v)); }

		CVec2 operator/(const CVec2& v) const;
		CVec2 operator*(const CVec2& v) const;

		void Set( real _x, real _y )			{ this->x = _x; this->y = _y; }


		operator real*()						{ return (real*)&x; }
		operator const real*() const			{ return (real*)&x; }

		real &operator[](int i)					{ return ((real*)&x)[i]; }
		const real operator[](int i) const		{ return ((real*)&x)[i]; }

		//! Длина вектора
		real Len( void ) const					{ return sqrt(x*x + y*y ); }

		//! Приводит вектор к единичному виду
		real Normalize();
	public:
		real x,y;
	};

	r_inline CVec2 CVec2::operator/(const CVec2& v) const {
		CVec2 vec;
		vec.x = x / v.x;
		vec.y = y / v.y;
		return vec;
	}

	r_inline CVec2 CVec2::operator*(const CVec2& v) const {
		CVec2 vec;
		vec.x = x * v.x;
		vec.y = y * v.y;
		return vec;
	}

	r_inline real CVec2::Normalize() {
		real inv,len = sqrt(x * x + y * y);

		if (len < EPSILON) 
			return 0.0;

		inv = 1.0f / len;
		x *= inv;
		y *= inv;

		return len;
	}

}
#endif