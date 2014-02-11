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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "updatesystem.h"

namespace rengine3d {

	CUpdateSystem::CUpdateSystem() {
	}

	CUpdateSystem::~CUpdateSystem() {
		this->Shutdown();
	}

	string_t CUpdateSystem::GetName(void) {
		return "CUpdateSystem";
	}

	string_t CUpdateSystem::GetDescription(void) {
		return "Update system";
	}

	string_t CUpdateSystem::GetVersion(void) {
		return "0.0.1";
	}

	bool CUpdateSystem::Init(void) {
		Log("  Initializing UpdateSystem...\n");
		this->AddContainer("Default");
		Log("  Created default container.\n");
		this->OnInit();

		return true;
	}

	void CUpdateSystem::Shutdown(void) {
		Log("  Shutdown UpdateSystem...\n");
		this->OnShutdown();
		m_updaterVars.clear();
		m_updaterContainer.clear();
	}

	void CUpdateSystem::Print(void) {
		updatersContainerIt_t	containerIt;
		updatersListIt_t		updaterIt;

		Log("\tRegistered %d update containers.\n", m_updaterContainer.size());
		Log("\tUpdater containers list:\n");

		for ( containerIt = m_updaterContainer.begin(); containerIt!=m_updaterContainer.end();++containerIt) {
			updatersList_t updatersList = containerIt->second;
			Log("\t\t'%s', registered %d updateables :\n", containerIt->first.c_str(), updatersList.size());
			for ( updaterIt = updatersList.begin(); updaterIt!=updatersList.end();++updaterIt) {
				Log("    %s\n", (*updaterIt)->GetName().c_str());
			}
		}

		Log("Updater variables:\n");

		for ( updatersListIt_t it = m_updaterVars.begin(); it!=m_updaterVars.end();++it) {
			Log("  %s\n", (*it)->GetName().c_str());
		}
	}

	void CUpdateSystem::OnInit(void) {
		for ( updatersListIt_t it = m_updaterVars.begin(); it!=m_updaterVars.end();++it) {
			(*it)->OnInit();
		}

		updatersContainerIt_t	containerIt;
		updatersListIt_t		updaterIt;

		for ( containerIt = m_updaterContainer.begin(); containerIt!=m_updaterContainer.end();++containerIt) {
			updatersList_t updatersList = containerIt->second;
			for ( updaterIt = updatersList.begin(); updaterIt!=updatersList.end();++updaterIt) {
				(*updaterIt)->OnInit();
			}
		}
	}

	void CUpdateSystem::OnShutdown(void) {
		for ( updatersListIt_t it = m_updaterVars.begin(); it!=m_updaterVars.end();++it) {
			(*it)->OnShutdown();
		}

		updatersContainerIt_t	containerIt;
		updatersListIt_t		updaterIt;

		for ( containerIt = m_updaterContainer.begin(); containerIt!=m_updaterContainer.end();++containerIt) {
			updatersList_t updatersList = containerIt->second;
			for ( updaterIt = updatersList.begin(); updaterIt!=updatersList.end();++updaterIt) {
				(*updaterIt)->OnShutdown();
			}
		}
	}

	void CUpdateSystem::OnDraw(void) {
		for ( updatersListIt_t it = m_updaterVars.begin(); it!=m_updaterVars.end();++it) {
			(*it)->OnDraw();
		}

		updatersContainerIt_t	containerIt;
		updatersListIt_t		updaterIt;

		for ( containerIt = m_updaterContainer.begin(); containerIt!=m_updaterContainer.end();++containerIt) {
			updatersList_t updatersList = containerIt->second;
			for ( updaterIt = updatersList.begin(); updaterIt!=updatersList.end();++updaterIt) {
				(*updaterIt)->OnDraw();
			}
		}
	}

	void CUpdateSystem::OnUpdate(real timeStep) {
		for ( updatersListIt_t it = m_updaterVars.begin(); it!=m_updaterVars.end();++it) {
			(*it)->OnUpdate(timeStep);
		}

		updatersContainerIt_t	containerIt;
		updatersListIt_t		updaterIt;

		for ( containerIt = m_updaterContainer.begin(); containerIt!=m_updaterContainer.end();++containerIt) {
			updatersList_t updatersList = containerIt->second;
			for ( updaterIt = updatersList.begin(); updaterIt!=updatersList.end();++updaterIt) {
				(*updaterIt)->OnUpdate(timeStep);
			}
		}
	}

	void CUpdateSystem::OnPostSceneDraw(void) {
		for ( updatersListIt_t it = m_updaterVars.begin(); it!=m_updaterVars.end();++it) {
			(*it)->OnPostSceneDraw();
		}

		updatersContainerIt_t	containerIt;
		updatersListIt_t		updaterIt;

		for ( containerIt = m_updaterContainer.begin(); containerIt!=m_updaterContainer.end();++containerIt) {
			updatersList_t updatersList = containerIt->second;
			for ( updaterIt = updatersList.begin(); updaterIt!=updatersList.end();++updaterIt) {
				(*updaterIt)->OnPostSceneDraw();
			}
		}
	}

	void CUpdateSystem::OnPostGUIDraw(void) {
		for ( updatersListIt_t it = m_updaterVars.begin(); it!=m_updaterVars.end();++it) {
			(*it)->OnPostGUIDraw();
		}

		updatersContainerIt_t	containerIt;
		updatersListIt_t		updaterIt;

		for ( containerIt = m_updaterContainer.begin(); containerIt!=m_updaterContainer.end();++containerIt) {
			updatersList_t updatersList = containerIt->second;
			for ( updaterIt = updatersList.begin(); updaterIt!=updatersList.end();++updaterIt) {
				(*updaterIt)->OnPostGUIDraw();
			}
		}
	}

	bool CUpdateSystem::AddUpdater(IUpdateable* updater, const string_t& container) {
		if (!updater)
			return false;

		updatersContainerIt_t it = m_updaterContainer.find(container);
		if (it == m_updaterContainer.end())
			return false;

		it->second.push_back(updater);

		return true;
	}

	bool CUpdateSystem::AddContainer(const string_t& name) {
		updatersContainerIt_t it;

		it = m_updaterContainer.find(name);
		if ( it != m_updaterContainer.end()) 
			return false;

		m_updaterContainer.insert(updatersContainer_t::value_type(name, updatersList_t()));

		return true;
	}

	bool CUpdateSystem::AddUpdaterVariable(IUpdateable* updaterVar) {
		if (!updaterVar)
			return false;

		m_updaterVars.push_back(updaterVar);

		return true;
	}

	void CUpdateSystem::ShowStatistics(const string_t& updateable, const string_t& container) {
		// TODO: show statistics

	}

}

