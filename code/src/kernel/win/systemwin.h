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

#ifndef __SYSTEM_WIN_H__
#define __SYSTEM_WIN_H__

namespace rengine3d {

	class CSystemWin: public ISystem {
		friend class CSystem;

	private:
		CSystemWin();
		virtual ~CSystemWin();

		virtual bool Init(void) override;
		virtual void Shutdown(void) override;

		virtual bool IsInitialized(void) override { return m_initialized; };

		virtual string_t GetName(void) override;
		virtual string_t GetDescription(void) override;
		virtual string_t GetVersion(void) override;

		virtual string_t GetOS() const override;
		virtual string_t GetPlatform() const override;
		virtual string_t GetComputerName() const override;
		virtual string_t GetUserName() const override;
		virtual string_t GetUserHomeDir() const override;
		virtual string_t GetUserDataDir() const  override;
		virtual string_t GetExecutableFilename() const override;
		virtual string_t GetCurrentDir() const override;
		virtual bool SetCurrentDir(const string_t& path) override;
		virtual void Exit(int ret) override;
		virtual uint64 GetMilliseconds() const override;
		virtual uint64 GetMicroseconds() const override;
		virtual void Sleep(uint64 milliseconds) const override;
		virtual char GetSeparator() const override;
	private:
		//bool m_initialized;

	};
}

#endif