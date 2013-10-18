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

#ifndef __CSYSTEM_H__
#define __CSYSTEM_H__

namespace rengine3d {
	class CSystem: public ISystem {
	public:
		CSystem();
		virtual ~CSystem();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual bool IsInitialized(void) { return m_system->IsInitialized(); };

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		string_t GetOS() const;
		string_t GetPlatform() const;
		string_t GetComputerName() const;
		string_t GetUserName() const;
		string_t GetUserHomeDir() const;
		string_t GetUserDataDir() const;
		string_t GetExecutableFilename() const;
		string_t GetCurrentDir() const;
		bool SetCurrentDir(const string_t& path);
		void Exit(int ret);
		uint64 GetMilliseconds() const;
		uint64 GetMicroseconds() const;
		void Sleep(uint64 milliseconds) const;
		char GetSeparator() const;
	private:
		ISystem*	m_system;
	};
}

#endif
