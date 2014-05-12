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

#ifndef __IRESOURCEMANAGER_H__
#define __IRESOURCEMANAGER_H__

namespace rengine3d {

	typedef IResource *(*ResTypeFactoryFunc)(const string_t& name);

	typedef struct {
		string_t typeString;
		ResTypeFactoryFunc factoryFunc;
	} resourceRegInfo_t;

	class IResourceManager: public ISubSystem {
	public:
		IResourceManager(){};
		virtual ~IResourceManager(){};

		virtual void RegisterType( uint type, const string_t& typeString, ResTypeFactoryFunc func) = 0;

		virtual void Clear(void) = 0;
		virtual bool Load(bool forceReload = false) = 0;
		virtual IResource* Add(const string_t& name, resourceType_t type) = 0;
		virtual void Remove(IResource* res) = 0;
		virtual IResource* Find(const string_t& name, resourceType_t type) = 0;
		virtual void List(resourceType_t type) = 0;
	};

}
#endif
