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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#if defined (_MSC_VER) && defined(WIN32) && defined(_DEBUG)

    #ifdef new
        #undef new
    #endif

#include <stdlib.h>

    #ifndef _CRTBLD
        // Needed when building with pure MS SDK
        #define _CRTBLD
    #endif


#include <stdexcept>
#define _CRTDBG_MAP_ALLOC

#ifdef _malloca
#undef _malloca
#endif

#include <crtdbg.h>

// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the allocations to be of _CLIENT_BLOCK type
// Compile options needed: /Zi /D_DEBUG /MLd
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#define new MYDEBUG_NEW

#endif

/*
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC) && defined(__cplusplus) && !defined(_DEBUG_NEW)
inline void* __cdecl operator new( size_t nSize, const char * pszFileName, int nLine )
{
	return ::operator new( nSize, _NORMAL_BLOCK, pszFileName, nLine );
}

#define _DEBUG_NEW new(__FILE__, __LINE__)
#define new _DEBUG_NEW
#endif
*/
#endif
