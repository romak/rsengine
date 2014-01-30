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

#ifndef __UPDATE_SYSTEM_H__
#define __UPDATE_SYSTEM_H__

namespace rengine3d {

	typedef std::list<IUpdateable*>				updatersList_t;
	typedef updatersList_t::iterator			updatersListIt_t;

	typedef std::map<string_t, updatersList_t>	updatersContainer_t;
	typedef updatersContainer_t::iterator		updatersContainerIt_t;

	class CUpdateSystem: public IUpdateSystem {
	public:
		CUpdateSystem();
		virtual ~CUpdateSystem();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		virtual void Print(void);

		virtual void OnInit(void);
		virtual void OnShutdown(void);
		virtual void OnDraw(void);
		virtual void OnUpdate(real timeStep);

		virtual void OnPostSceneDraw(void);
		virtual void OnPostGUIDraw(void);

		virtual bool AddUpdater(IUpdateable* updater, const string_t& container);
		virtual bool AddContainer(const string_t& name);
		virtual bool AddUpdaterVariable(IUpdateable* updaterVar);

		virtual void ShowStatistics(const string_t& updateable = "All", const string_t& container = "Default");
	protected:
		updatersList_t		m_updaterVars;
		updatersContainer_t	m_updaterContainer;
	};

}
#endif
