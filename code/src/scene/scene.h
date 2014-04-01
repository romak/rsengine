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

#ifndef __CSCENE_H__
#define __CSCENE_H__

namespace rengine3d {

	typedef std::vector<ICamera*> cameraList_t;

	class CScene: public IScene {
	public:
		CScene();
		virtual ~CScene();

		virtual void OnUpdate(real timeStep);
		virtual void OnDraw(void);

		virtual ICamera3D* CreateCamera3D(const string_t& name); 

	private:
		INode*	m_root;

		cameraList_t	m_cameraList;
		ICamera*		m_activeCamera;
	};

}

#endif
