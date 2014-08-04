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
#include "log.h"

namespace rengine3d {

	CLog::CLog(const string_t& fileName, ILogWriter* logWriter): m_enabled(true), m_fileName(fileName), m_logWriter(logWriter), m_logLevel(logLevel_Low) {
	}

	CLog::~CLog() {
		m_history.clear();
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
		logEvent_t ev;
		char	text[MAX_LOG_LENGHT];
		va_list	ap;	

		if (!m_enabled) 
			return;

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);

		ev = MakeLogEvent(logEventType_Event, CVec4(0,0,0,0), 0, logLevel_Low);

		ev.line = text;

		this->Log(&ev);
	}

	void CLog::Warning(const char *format, ...) {
		logEvent_t ev;
		char	text[MAX_LOG_LENGHT];
		va_list	ap;	

		if (!m_enabled) 
			return;

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);

		MakeLogEvent(logEventType_Warning, CVec4(0,0,0,0), 0, logLevel_Medium);

		ev.line = text;

		this->Log(&ev);
	}

	void CLog::Error(const char *format, ...) {
		logEvent_t ev;
		char	text[MAX_LOG_LENGHT];
		va_list	ap;	

		if (!m_enabled) 
			return;

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);

		MakeLogEvent(logEventType_Error, CVec4(0,0,0,0), 0, logLevel_High);

		ev.line = text;

		this->Log(&ev);
	}

	logEvent_t CLog::MakeLogEvent(logEventType_t type, CVec4 color, uint module, logLevel_t level) {
		logEvent_t ev;
		ev.type = type;
		ev.color = color;
		ev.module = module;
		ev.level = level;
		return ev;
	}

	void CLog::Log(logEvent_t* logEvent) {

		string_t str, strType;
		time_t aclock;
		time( &aclock );

		struct tm * utcTime= localtime( &aclock  );

		switch (logEvent->type) {
		case logEventType_Event: 
			{
				strType = " ";
				break;
			}
		case logEventType_Warning: 
			{
				strType = "Warning: ";
				break;
			}
		case logEventType_Error: 
			{
				strType = "Error: ";
				break;
			}
		}
		char buff[32];
		sprintf(buff, "%02d-%02d-%04d %02d:%02d:%02d: %s", utcTime->tm_mday, utcTime->tm_mon+1, utcTime->tm_year+1900, 
			utcTime->tm_hour, utcTime->tm_min,utcTime->tm_sec, strType.c_str());
		str = buff + strType;
		str = str + logEvent->line;

		if (m_history.size() == MAX_LOG_HISTORY)
			m_history.erase(m_history.begin());

		m_history.push_back(*logEvent);

		m_logWriter->Write(str);

#if defined(PLATFORM_WIN32) && defined(_DEBUG)
		OutputDebugString(str.c_str());
#endif

	}

}