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

#ifndef __IINPUTDEVICE_H__
#define __IINPUTDEVICE_H__

namespace rengine3d {

	class IInputDevice: public CRefCount {
	public:
		IInputDevice(){};
		virtual ~IInputDevice(){};

		virtual bool Init(void) = 0;
		virtual void Shutdown(void) = 0;

		virtual void Update(void)=0;
		//virtual void PushEvent(void* _event) = 0;
		//virtual void Clear(void) = 0;

		virtual inputDeviceType_t GetType(void) = 0;
		virtual string_t GetName(void) = 0;
	protected:
		inputDeviceType_t	m_type;
		string_t			m_name;
	};
}

#endif
