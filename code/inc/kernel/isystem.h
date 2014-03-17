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

#ifndef __ISYSTEM_H__
#define __ISYSTEM_H__

namespace rengine3d {

	class ISystem: public ISubSystem  {
		friend class CSystem;
	public:
		ISystem(){};
		virtual ~ISystem(){};

		virtual string_t GetOS() const = 0;
		virtual string_t GetPlatform() const = 0;
		virtual string_t GetComputerName() const = 0;
		virtual string_t GetUserName() const = 0;
		virtual string_t GetUserHomeDir() const = 0;
		virtual string_t GetUserDataDir() const = 0;
		virtual string_t GetExecutableFilename() const = 0;
		virtual string_t GetCurrentDir() const = 0;
		virtual bool SetCurrentDir(const string_t& path) = 0;
		virtual void Exit(int ret) = 0;
		virtual uint64 GetMilliseconds() const = 0;
		virtual uint64 GetMicroseconds() const = 0;
		virtual void Sleep(uint64 milliseconds) const = 0;
		virtual char GetSeparator() const = 0;
	};
}

#endif

