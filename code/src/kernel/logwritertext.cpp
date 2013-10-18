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
#include "logwritertext.h"

namespace rengine3d {

	CLogWriterText::CLogWriterText(const string_t& fileName): m_fileName(fileName) {
		 fopen_s(&m_handle,m_fileName.c_str(), "w");
	}

	CLogWriterText::~CLogWriterText() {
		if (m_handle) 
			fclose(m_handle);
	}

	void CLogWriterText::Write(const string_t& message) {
		if (m_handle) {
			fprintf(m_handle, message.c_str());
			fflush(m_handle);
		}
	}

	void CLogWriterText::Clear() {
		if (m_handle) {
			fopen_s(&m_handle, m_fileName.c_str(), "w");
			fflush(m_handle);
		}
	}

}