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

	class CScene: public IScene {
	public:
		CScene();
		virtual ~CScene();

		virtual void AddCamera3D(ICamera3D* camera);
		virtual ICamera3D* CreateCamera3D(void); 

	private:
		CNode*	m_root;
		CNode*	m_cameraNode;
	};

}

#endif
