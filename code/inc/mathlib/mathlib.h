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

#ifndef __MATHLIB_H__
#define __MATHLIB_H__

#ifdef PI // чтобы небыло коллизий с ранними предопределени€ми
#undef PI
#endif

#ifdef PI64 // чтобы небыло коллизий с ранними предопределени€ми
#undef PI64
#endif

namespace rengine3d {
/*
	class CVec2;
	class CVec3;
	class CVec4;
	class CMat4;
	class CQuat;
	class CRay;
	class CBoundBox;
	class CBoundSphere;
	class CFrustum;
	class CRect;
*/
	//!  онстанта дл€ числа PI.
	const real PI			= 3.14159265359f;

	//!  онстанта дл€ половины числа PI.
	const real HALF_PI		= PI/2.0f;

	//!  онстанта дл€ конвертации из градусов в радианы 
	const real DEG2RAD		= PI / 180.0f;

	//!  онстанта дл€ конвертации из радиан в градусы
	const real RAD2DEG		= 180.0f / PI;

	const real EPSILON		=	1e-6f;

	//!  ласс содержит процедуры и структуры обработки математический действий
	class CMathLib {
	public:
	};

	r_inline int Log2Int(int value) {
		switch (value) {
		case 1:		return 0;
		case 2:		return 1;
		case 4:		return 2;
		case 8:		return 3;
		case 16:	return 4;
		case 32:	return 5;
		case 64:	return 6;
		case 128:	return 7;
		case 256:	return 8;
		case 512:	return 9;
		case 1024:	return 10;
		default: return 0; // TODO
		};

	}

	r_inline float DegreesToRadians(float degrees){
		return (degrees * PI) / 180.0f;
	}

	r_inline bool CloseEnough(real f1, real f2){
		// Determines whether the two floating-point values f1 and f2 are
		// close enough together that they can be considered equal.
		return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < EPSILON;
	}

	r_inline float RadiansToDegrees(float radians){
		return (radians * 180.0f) / PI;
	}

}

#endif
