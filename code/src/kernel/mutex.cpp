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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "mutex.h"
#include "win\mutexwin.h"

namespace rengine3d {

	CMutex::CMutex(): m_mutex(NULL) {
		#if PLATFORM == PLATFORM_WIN32
			m_mutex = new CMutexWin();
		#elif defined(PLATFORM_LINUX)
		#else
		#endif
	}

	CMutex::~CMutex() {
		SafeDelete(m_mutex);
	}

	bool CMutex::Lock() {
		return m_mutex->Lock();
	}

	bool CMutex::UnLock() {
		return m_mutex->UnLock();
	}

}