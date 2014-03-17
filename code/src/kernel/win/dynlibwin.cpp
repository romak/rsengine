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
#include "dynlibwin.h"

namespace rengine3d {

	CDynLibWin::CDynLibWin() {
	}

	CDynLibWin::~CDynLibWin() {
		this->Unload();
	}

	bool CDynLibWin::Load(const string_t& path) {
		if (m_hModule)
			return false; // Error!

		// Load library
		m_hModule = ::LoadLibraryExA(path.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);

		// Return whether loading of the library was successful

		return ((m_hModule) ? true: false);
	}

	bool CDynLibWin::IsLoaded() const {
		return (m_hModule != nullptr);
	}

	bool CDynLibWin::Unload() {
		if (m_hModule != nullptr) {
			if (::FreeLibrary(m_hModule)) {
				m_hModule = nullptr;
				return true;
			}
		}
		return false;
	}

	void* CDynLibWin::GetSymbol(const string_t& symbol) const {
		return m_hModule ? ::GetProcAddress(m_hModule, symbol.c_str()) : nullptr;
	}

}
