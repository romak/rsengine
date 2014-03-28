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
#include "camera3d.h"

namespace rengine3d {

	CCamera3D::CCamera3D() {
		m_fov		= 60.0f;
		m_aspect	= 1.3333f;
		m_near		= 1.0f;
		m_far		= 3000.0f;
	}

	CCamera3D::CCamera3D(real fov, real aspect, real _near, real _far) {
		m_fov		= fov;
		m_aspect	= aspect;
		m_near		= _near;
		m_far		= _far;
	}

	CCamera3D::~CCamera3D() {
	}

	void CCamera3D::SetModelViewMatrix(IRenderDriver* renderDriver) {

	}

	void CCamera3D::SetProjectionMatrix(IRenderDriver* renderDriver) {

	}

	void CCamera3D::UpdateProjectionMatrix(void) {

	}

	real CCamera3D::GetFov(void) {
		return m_fov;
	}

	real CCamera3D::GetAspect(void) {
		return m_aspect;
	}

	real CCamera3D::GetNear(void) {
		return m_near;
	}

	real CCamera3D::GetFar(void) {
		return m_far;
	}

	void CCamera3D::SetFov(real fov) {
		m_fov = fov;
	}

	void CCamera3D::SetAspect(real aspect) {
		m_aspect = aspect;
	}

	void CCamera3D::SetNear(real _near) {
		m_near = _near;
	}

	void CCamera3D::SetFar(real _far) {
		m_far = _far;
	}

	void CCamera3D::SetLens(real focalLength, real frameHeight) {
	}

	void CCamera3D::SetViewOffset(real fullWidth, real fullHeight, real x, real y, real width, real height) {
	}

}