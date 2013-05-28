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

#ifndef __IUPDATEABLE_H__
#define __IUPDATEABLE_H__

namespace rengine3d {

	class IUpdateable: public CRefCount {
	public:
		IUpdateable(){};
		IUpdateable(const string_t& name): m_updatableName(name){};

		virtual ~IUpdateable(){};
		virtual const string_t& GetUpdateableName(void) { return m_updatableName; };

		virtual bool OnInit(void){ return true;};
		virtual void OnShutdown(void){};
		virtual void OnDraw(void){};

		virtual void OnUpdate(real timeStep){};

		virtual void OnPostSceneDraw(){}
		virtual void OnPostGUIDraw(){}
	protected:
		string_t	m_updatableName;
	};

}

#endif
