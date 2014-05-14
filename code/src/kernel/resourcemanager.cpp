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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "resourcemanager.h"
#include "../render/sdl/texture_sdl.h"

namespace rengine3d {

	CResourceManager::CResourceManager(IFileSystem* fileSys): m_fileSys(fileSys) {
	}

	CResourceManager::~CResourceManager() {
		this->Shutdown();
	}

	bool CResourceManager::Init(void) {
		Log("\tInitializing resource manager...\n");

		this->RegisterType(resourceType_t::Texture, "Texture", CTextureSDL::FactoryFunc);

		return true;
	}

	void CResourceManager::Shutdown(void) {
		Log("\tShutdown resource manager...\n");
		this->Clear();
	}

	string_t CResourceManager::GetName(void) {
		return "CResourceManager";
	}

	string_t CResourceManager::GetDescription(void) {
		return "CResourceManager";
	}

	string_t CResourceManager::GetVersion(void) {
		return "0.0.1";
	}

	void CResourceManager::RegisterType( uint type, const string_t& typeString, ResTypeFactoryFunc func) {
		resourcesRegInfoIt_t it = m_regInfo.find(type) ;
		if ( it == m_regInfo.end() ) {
			Log("\t\tRegistering new resource type: %s\n", typeString.c_str());
			resourceRegInfo_t regInfo;
			regInfo.typeString	= typeString;
			regInfo.factoryFunc = func;
			m_regInfo.insert( resourcesRegInfo_t::value_type( type, regInfo) );
		}
	}

	void CResourceManager::Clear(void) {

		for ( resourcesMapIt_t it = m_resources.begin(); it != m_resources.end(); ++it ) {
			SafeDelete(it->second);
		}

		m_resources.clear();
		m_regInfo.clear();
	}

	bool CResourceManager::Load(bool forceReload) {
		uint notLoaded = 0;

		for ( resourcesMapIt_t it = m_resources.begin(); it != m_resources.end(); ++it ) {
			string_t name = it->second->GetName();
			// TODO: load data from file

			IFile* file = m_fileSys->OpenFile(name.c_str(), fileMode_Read);
			if ( !file ) {
				Warning( "Resource not found: %s\n", name.c_str());
				SafeDelete(file);
				return false;
			}

			uint size	= file->Length();
			char* data	= new char [size];
			file->Read(data, size);

			if (forceReload) {
				string_t strInfo = "Loading:"+it->second->GetName();
				if (!it->second->Load(data, size)) {
					notLoaded++;
					strInfo += " - error.";
				} else{
					strInfo += " - ok.";
				}
				Log("%s\n", strInfo.c_str());
			} else {
				string_t strInfo = "Loading: "+it->second->GetName();
				if (!it->second->IsLoaded()) {
					if (!it->second->Load(data, size)) {
						notLoaded++;
						strInfo += " - error.";
					}else {
						strInfo += " - ok.";
					}
					Log("%s\n", strInfo.c_str());
				}
			}

			SafeArrayDelete(data);
			SafeDelete(file);
		}

		return true;
	}

	IResource* CResourceManager::Add(const string_t& name, resourceType_t type) {

		resourcesRegInfoIt_t it = m_regInfo.find(type) ;
		if ( it == m_regInfo.end() ) {
			Error("Resource type %d not registered !\n", type);
			return NULL;
		}

		IResource* res = it->second.factoryFunc(name);
		if (!res) {
			return NULL;
		}

		string_t resHash = GetHashStr(name, type);

		m_resources.insert( resourcesMap_t::value_type( resHash, res) );

		return res;
	}

	string_t CResourceManager::GetHashStr(const string_t& name, resourceType_t type) {
		std::stringstream ss;
		ss << type << "#" << name << '\0';
		string_t str = ss.str();
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}

	void CResourceManager::Remove(IResource* res) {
	}

	IResource* CResourceManager::Find(const string_t& name, resourceType_t type) {
		string_t resHash = GetHashStr(name, type);

		resourcesMapIt_t it = m_resources.find(resHash);
		if (it==m_resources.end())
			return NULL;
		return it->second;
	}

	void CResourceManager::List(resourceType_t type) {
		Log("Resources list:\n");

		for ( resourcesMapIt_t it = m_resources.begin(); it != m_resources.end(); ++it ) {
			string_t loaded =  (it->second->IsLoaded() ? "loaded" : "not loaded");
			if (type == resourceType_t::All) {
				Log("\t%s - %s\n", it->second->GetName().c_str(), loaded.c_str());
			} else {
				if (it->second->GetType() == type) {
					Log("\t%s - %s\n", it->second->GetName().c_str(), loaded.c_str());
				}
			}
		}
	}


}


