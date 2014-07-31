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

#ifndef __ILOG_H__
#define __ILOG_H__

namespace rengine3d {

	const int MAX_LOG_LENGHT	= 256;
	const int MAX_LOG_HISTORY	= 128;

	//! Структура содержащая описание типа лога
	typedef enum {
		logEventType_Unknown,
		logEventType_Debug,
		logEventType_Game,
		logEventType_Event,
		logEventType_Warning,
		logEventType_Error
	}logEventType_t;

	typedef enum {
		logLevel_Low,
		logLevel_Medium,
		logLevel_High
	}logLevel_t;

	//! Описания сообщения выведенного в лог
	typedef struct {
		string_t		line;
		logEventType_t	type;
		CVec4			color;
		uint			module;
		logLevel_t		level;
	}logEvent_t;

	//! Интерфейс класса, для лога важных событий на протяжение работы движка
	class ILog {
	public:
		virtual ~ILog(){};

		virtual void SetEnabled(bool value) = 0;
		virtual bool IsEnabled() = 0;

		virtual void SetLogLevel(logLevel_t level) = 0;

		virtual void Print(int eventType, const string_t& srcFile, const string_t& funcName, int line, const char* message, ...) = 0;
		virtual void Print(const char *format, ...) = 0;
		virtual void Warning(const char *format, ...) = 0;
		virtual void Error(const char *format, ...) = 0;
		virtual void Log(logEvent_t* logEvent) = 0;
	};

	extern void Log(const char *format, ...);
	extern void Warning(const char *format, ...);
	extern void Error(const char *format, ...);

}
#endif
