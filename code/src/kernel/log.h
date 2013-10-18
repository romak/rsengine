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

#ifndef __CLOG_H__
#define __CLOG_H__

namespace rengine3d {

	class ILog;
	class ILogWriter;

	class CLog: public ILog {
	public:
		CLog(const string_t& fileName, ILogWriter*	logWriter);
		virtual ~CLog();

		virtual void SetEnabled(bool value);
		virtual bool IsEnabled();

		virtual void SetLogLevel(logLevel_t level);

		virtual void Print(int eventType, const string_t& srcFile, const string_t& funcName, int line, const char* message, ...);
		virtual void Print(const char *format, ...);
		virtual void Warning(const char *format, ...);
		virtual void Error(const char *format, ...);
	protected:
		bool		m_enabled;
		string_t	m_fileName;
		ILogWriter*	m_logWriter;
		logLevel_t	m_logLevel;
	};
}

#endif
