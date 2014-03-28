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
		m_root			= new CNode("root");
		m_cameraNode	= new CNode("camera");

		m_cameraNode->Attach(m_root);
	}

	CScene::~CScene() {
		SafeDelete(m_root);
	}

	void CScene::AddCamera3D(ICamera3D* camera) {
	}

	ICamera3D* CScene::CreateCamera3D(void) {
		return new CCamera3D();
	}


}