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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "mutexwin.h"

namespace rengine3d {

	CMutexWin::CMutexWin() {
		m_hMutex = CreateMutex(nullptr, false, nullptr);
	}

	CMutexWin::~CMutexWin() {
		if (m_hMutex)
			CloseHandle(m_hMutex);
	}

	bool CMutexWin::Lock() {
		return (m_hMutex && WaitForSingleObject(m_hMutex, INFINITE) == WAIT_OBJECT_0);
	}

	bool CMutexWin::UnLock() {
		return (m_hMutex && ReleaseMutex(m_hMutex));
	}

}
