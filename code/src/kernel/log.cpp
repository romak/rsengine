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
#include "log.h"

namespace rengine3d {

	CLog::CLog(const string_t& fileName, ILogWriter* logWriter): m_enabled(true), m_fileName(fileName), m_logWriter(logWriter), m_logLevel(logLevel_Low) {
	}

	CLog::~CLog() {
	}

	void CLog::SetEnabled(bool value) {
		m_enabled = value;
	}

	bool CLog::IsEnabled() {
		return m_enabled;
	}

	void CLog::SetLogLevel(logLevel_t level) {
		m_logLevel = level;
	}

	void CLog::Print(int eventType, const string_t& srcFile, const string_t& funcName, int line, const char* message, ...) {
		if (!m_enabled) 
			return;
	}

	void CLog::Print(const char *format, ...) {
		char	text[4096];
		va_list	ap;	

		if (!m_enabled) 
			return;

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);

		m_logWriter->Write(text);

#if defined(PLATFORM_WIN32) && defined(_DEBUG)
		OutputDebugStringA( text );
#endif

	}

	void CLog::Warning(const char *format, ...) {
		char	text[4096];
		va_list	ap;	

		if (!m_enabled) 
			return;

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);
		
		string_t str = "Warning: ";
		str += text;

		m_logWriter->Write(str);

#if defined(PLATFORM_WIN32) && defined(_DEBUG)
		OutputDebugStringA( text );
#endif
	}

	void CLog::Error(const char *format, ...) {
		char	text[4096];
		va_list	ap;	

		if (!m_enabled) 
			return;

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);
		
		string_t str = "Error: ";
		str += text;

		m_logWriter->Write(str);

#if defined(PLATFORM_WIN32) && defined(_DEBUG)
		OutputDebugStringA( text );
#endif

	}

}