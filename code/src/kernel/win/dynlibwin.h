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

#ifndef __CDYNLIBWIN_H__
#define __CDYNLIBWIN_H__

namespace rengine3d {

	class CDynLibWin: public IDynLib {
		friend class CDynLib;
	private:
		CDynLibWin();
		virtual ~CDynLibWin();

		virtual bool Load(const string_t& path) override;
		virtual bool IsLoaded() const override;
		virtual bool Unload() override;
		virtual void *GetSymbol(const string_t& symbol) const override;
	private:
		HMODULE m_hModule;
	};

}

#endif
