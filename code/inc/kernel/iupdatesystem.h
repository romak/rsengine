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

#ifndef __IUPDATESYSTEM_H__
#define __IUPDATESYSTEM_H__

namespace rengine3d {

	class IUpdateable;

	class IUpdateSystem: ISubSystem {
	public:
		IUpdateSystem(){};
		virtual ~IUpdateSystem(){};

		virtual bool Init(void) = 0;
		virtual void Shutdown(void) = 0;

		virtual void Print(void) = 0;

		virtual void OnInit(void) = 0;
		virtual void OnShutdown(void) = 0;
		virtual void OnDraw(void) = 0;
		virtual void OnUpdate(real timeStep) = 0;

		virtual void OnPostSceneDraw() = 0;
		virtual void OnPostGUIDraw() = 0;

		virtual bool AddUpdater(IUpdateable* updater, const string_t& container = "Default") = 0;
		virtual bool AddContainer(const string_t& name) = 0;
		virtual bool AddUpdaterVariable(IUpdateable* updaterVar) = 0;

		virtual void ShowStatistics(const string_t& updateable = "All", const string_t& container = "Default") = 0;
	};

}

#endif
