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

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

//! Define supported platforms
#define PLATFORM_WIN32	1
#define PLATFORM_LINUX	2
#define PLATFORM_APPLE	3

//! Define supported compilers
#define COMPILER_MSVC	1
#define COMPILER_GNUC	2

#define ENDIAN_LITTLE	1
#define ENDIAN_BIG		2

//! Define supported processors archetectures
#define ARCHITECTURE_32	1
#define ARCHITECTURE_64	2

#define USE_SDL	1

//! Define current build
#ifdef  _DEBUG
#   define BUILD_STR "DEBUG"
#elif NDEBUG
#   define BUILD_STR "RELEASE"
#else
#   define BUILD_STR "OTHER"
#endif

#if defined (__GNUC__)
#	define COMPILER_STR "GCC"
#endif

#if defined( _MSC_VER )
#   define COMPILER		COMPILER_MSVC
#   define COMP_VERSION _MSC_VER
#	define COMPILER_STR "VS"
#else
#   pragma error "Eror! Unknown compiler!"
#endif

//! Define current platform
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define PLATFORM PLATFORM_WIN32
#   define PLATFORM_STR "WIN32"
	#define WIN32_LEAN_AND_MEAN 
	#include <shlobj.h>

#elif defined( __APPLE_CC__) || defined( __APPLE__ )
#   define PLATFORM PLATFORM_APPLE
#   define PLATFORM_STR "APPLE"

#else
#   define PLATFORM PLATFORM_LINUX
#   define PLATFORM_STR "LINUX"
#endif

//! Define current architecture
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define ARCHITECTURE_TYPE ARCHITECTURE_64
#	define ARCHITECTURE_STR "x64"
#else
#   define ARCHITECTURE_TYPE ARCHITECTURE_32
#	define ARCHITECTURE_STR "x32"
#endif

//! Define write byte order
#ifdef CONFIG_BIG_ENDIAN
#    define ENDIAN ENDIAN_BIG
#else
#    define ENDIAN ENDIAN_LITTLE
#endif

#if COMPILER == COMPILER_MSVC
	typedef unsigned __int64	uint64;
#else
	typedef unsigned long long	uint64;
#endif

//! String of current engine build
#define	BUILD_STRING PLATFORM_STR "-"\
	COMPILER_STR "-"\
	ARCHITECTURE_STR "-"\
	BUILD_STR "-"\
	__DATE__ "-"\
	__TIME__

#endif

