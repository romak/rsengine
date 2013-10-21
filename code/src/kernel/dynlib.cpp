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
#include "dynlib.h"
#include "win\dynlibwin.h"

namespace rengine3d {

	CDynLib::CDynLib(): m_dynLib(NULL) {
		#if PLATFORM == PLATFORM_WIN32
			m_dynLib = new CDynLibWin();
		#elif defined(PLATFORM_LINUX)
		#else
		#endif
	}

	CDynLib::~CDynLib() {		
		SafeDelete(m_dynLib);
	}

	bool CDynLib::Load(const string_t& path) {		
		return m_dynLib->Load(path);
	}

	bool CDynLib::IsLoaded() const {		
		return m_dynLib->IsLoaded();
	}

	bool CDynLib::Unload() {
		return m_dynLib->Unload();
	}

	void* CDynLib::GetSymbol(const string_t& symbol) const {		
		return m_dynLib->GetSymbol(symbol);
	}

};
