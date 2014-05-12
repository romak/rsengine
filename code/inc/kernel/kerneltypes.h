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

#ifndef __KERNELTYPES_H__
#define __KERNELTYPES_H__

//! For double precision
#if DOUBLE_PRECISION == 1
	typedef double	real;
#else
    typedef float	real;
#endif

typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;
typedef unsigned long		dword;
typedef __int64				int64;
typedef unsigned __int64	uint64;

#ifndef BIT
#define BIT( num ) ( 1 << ( num ) )
#endif

#ifndef NULL
#define NULL (0L)
#endif

#define SafeDelete(p)		{ if(p) { delete p;  p=NULL; } }
#define SafeArrayDelete(p)	{ if(p) { delete [] p;  p=NULL; } }
#define SafeRelease(p)		{ if(p) { p->Release(); } }

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <string>

// STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <exception>

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

extern "C" {

#include <sys/types.h>
#include <sys/stat.h>

}

#if WCHAR_STRINGS
	typedef std::wstring	_String;
#else
	typedef std::string		_String;
#endif

typedef _String						string_t;
typedef std::vector<string_t>		stringVector_t;

typedef std::vector<uint>			uintVector_t;
typedef uintVector_t::iterator		uintVectorIt_t;

typedef std::vector<real>			realVector_t;
typedef realVector_t::iterator		realVectorIt_t;

typedef std::vector<float>			floatVector_t;
typedef floatVector_t::iterator		floatVectorIt_t;

#ifndef r_inline
//#	define r_inline inline
#	define r_inline __forceinline

#endif

#endif
