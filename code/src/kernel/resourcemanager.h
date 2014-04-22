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

#ifndef __CRESOURCEMANAGER_H__
#define __CRESOURCEMANAGER_H__	

namespace rengine3d {
	typedef struct {
		string_t	name;
		uint		type;
	} resourceHash_t;

//	typedef std::map<resourceHash_t*, IResource*>	resourcesMap_t;
	typedef std::map<string_t, IResource*>	resourcesMap_t;
	typedef resourcesMap_t::iterator				resourcesMapIt_t;

	typedef std::map<uint, resourceRegInfo_t>		resourcesRegInfo_t;
	typedef resourcesRegInfo_t::iterator			resourcesRegInfoIt_t;

	class CResourceManager: public IResourceManager {
	public:
		CResourceManager(IFileSystem* fileSys);
		virtual ~CResourceManager();
		
		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		virtual void RegisterType( uint type, const string_t& typeString, ResTypeFactoryFunc func);

		virtual void Clear(void);
		virtual bool Load(void);
		virtual IResource* Add(const string_t& name, resourceType_t type);
		virtual void Remove(IResource* res);
		virtual IResource* Find(const string_t& name, resourceType_t type);
		virtual void List(resourceType_t type);
	private:
		string_t GetHashStr(const string_t& name, resourceType_t type);
	private:
		resourcesMap_t			m_resources;
		IFileSystem*			m_fileSys;
		resourcesRegInfo_t		m_regInfo;
	};
}

#endif
