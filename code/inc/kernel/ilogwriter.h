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

#ifndef __ILOG_WRITER_H__
#define __ILOG_WRITER_H__

namespace rengine3d {

	//!  ласс дл€ записи лога в файл (по умолчанию использетс€ текстовый формат)
	//! ¬озможно перегрузить к примеру дл€ записи в HTML
	class ILogWriter {
	public:
		ILogWriter(){};
		virtual ~ILogWriter(){};

		virtual void Write(const string_t& message) = 0;
		virtual void Clear(void) = 0;
	};
}

#endif
