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

#ifndef __ICONSOLE_H__
#define __ICONSOLE_H__

namespace rengine3d {

	class IConsole: public IUpdateable, public ISubSystem {
	public:
		IConsole(const string_t& name) : IUpdateable(name){};
		virtual ~IConsole(){};
		
		virtual void Clear() = 0;
		virtual bool IsActive() = 0;
		virtual void Print(const char *text) = 0;
	};
}

#endif
