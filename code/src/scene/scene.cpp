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
#include "scene.h"
#include "camera3d.h"

namespace rengine3d {

	CScene::CScene() {
		m_root			= new INode("root");
	}

	CScene::~CScene() {

		for ( cameraList_t::iterator it = m_cameraList.begin(); it != m_cameraList.end(); ++it ) {
			SafeDelete(*it);
		}

		m_cameraList.clear();

		SafeDelete(m_root);
	}

	void CScene::OnUpdate(real timeStep) {

	}

	void CScene::OnDraw(void) {
	}

	ICamera3D* CScene::CreateCamera3D(const string_t& name) {
		ICamera3D* camera = new CCamera3D(name);
		m_cameraList.push_back(camera);
		return camera;
	}


}