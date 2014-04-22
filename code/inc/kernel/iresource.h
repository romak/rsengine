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

#ifndef __IRESOURCE_H__
#define __IRESOURCE_H__

namespace rengine3d {

	typedef enum {
		Unknown = 0,
		Mesh,
		Material,
		Texture,
		Shader,
		All
	} resourceType_t;

	class IResource: public IRefCount {
	public:
		IResource(const string_t& name, resourceType_t type):m_size(0),m_loaded(false),m_name(name), m_type(type) {};
		virtual ~IResource(){};

		virtual bool Load(const char* data, uint size) = 0;
		virtual void UnLoad(void) = 0;

		virtual string_t GetName(void) {return m_name;};
		virtual resourceType_t GetType(void) { return m_type;};
		virtual bool IsLoaded(void) {return m_loaded;};
		virtual uint GetSize(void) {return m_size;};
	protected:
		string_t		m_name;
		uint			m_size;
		bool			m_loaded;
		resourceType_t	m_type;
	};

}
#endif
