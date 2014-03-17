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

#ifndef __CFRUSTUM_H__
#define __CFRUSTUM_H__

namespace rengine3d {

	typedef enum {
		frustumPlane_Left	= 0,
		frustumPlane_Right	= 1,
		frustumPlane_Bottom	= 2,
		frustumPlane_Top	= 3,
		frustumPlane_Near	= 4,
		frustumPlane_Far	= 5,
		frustumPlane_Count	= 6
	}frustumPlane_t;

	class IRenderDriver;

	class CFrustum {
	public:
		CFrustum();
		~CFrustum(){};

		CPlane GetPlane(frustumPlane_t plane);

		void SetViewProjMatrix(const CMat4& proj, const CMat4& view, real ZFar, real ZNear, real FOV,real aspect);
		void BuildPlanes(void);

		virtual real GetFOV() const;
		virtual void SetFOV(real fov);

		virtual real GetAspect() const;
		virtual void SetAspect(real aspect);

		// collisions functions
		bool BoxInFrustum(const CBoundBox& box) const;
		bool PointInFrustum(const CVec3& point) const;
		bool SphereInFrustum(const CBoundSphere& sphere) const;

		void Draw(IRenderDriver* renderDriver);
	protected:
		CPlane	m_planes[6];
		real	m_farPlane;
		real	m_nearPlane;
		real	m_aspect;
		real	m_fov;
		CMat4	m_viewProj;
		CMat4	m_modelView;
	};

	r_inline CFrustum::CFrustum() {
		m_farPlane	= 0;
		m_nearPlane	= 0;
		m_aspect	= 0;
		m_fov		= 0;
	}

	r_inline CPlane CFrustum::GetPlane(frustumPlane_t plane) {
		return m_planes[plane];
	}

	r_inline real CFrustum::GetFOV() const {
		return m_fov;
	}

	r_inline real CFrustum::GetAspect() const {
		return m_aspect;
	}

	r_inline void CFrustum::SetFOV(real fov) {
		m_fov = fov;
	}

	r_inline void CFrustum::SetAspect(real aspect) {
		m_aspect = aspect;
	}

	r_inline void CFrustum::SetViewProjMatrix(const CMat4& proj, const CMat4& view, real ZFar, real ZNear, real FOV,real aspect) {
		m_farPlane	= ZFar;
		m_nearPlane	= ZNear;
		m_aspect	= aspect;
		m_fov		= FOV;

		m_viewProj	= (proj * view);
		m_modelView = view;

		this->BuildPlanes();
	}

	r_inline void CFrustum::BuildPlanes(void) {
		// Extracts the view frustum clipping planes from the combined
		// view-projection matrix in world space. The extracted planes will
		// have their normals pointing towards the inside of the view frustum.
		//
		// References:
		//  Gil Gribb, Klaus Hartmann, "Fast Extraction of Viewing Frustum
		//  Planes from the World-View-Projection Matrix,"
		//  http://www2.ravensoft.com/users/ggribb/plane%20extraction.pdf

		CPlane* plane = 0;

		// Left clipping plane.
		plane = &m_planes[frustumPlane_Left];
		plane->Set(	
			m_viewProj[0][3] + m_viewProj[0][0], 
			m_viewProj[1][3] + m_viewProj[1][0],
			m_viewProj[2][3] + m_viewProj[2][0], 
			m_viewProj[3][3] + m_viewProj[3][0]);
		plane->Normalize();

		// Right clipping plane.
		plane = &m_planes[frustumPlane_Right];
		plane->Set(	
			m_viewProj[0][3] + m_viewProj[0][0],
			m_viewProj[1][3] + m_viewProj[1][0],
			m_viewProj[2][3] + m_viewProj[2][0], 
			m_viewProj[3][3] + m_viewProj[3][0]);
		plane->Normalize();

		// Top clipping plane.
		plane = &m_planes[frustumPlane_Top];
		plane->Set(	
			m_viewProj[0][3] + m_viewProj[0][1],
			m_viewProj[1][3] + m_viewProj[1][1],
			m_viewProj[2][3] + m_viewProj[2][1], 
			m_viewProj[3][3] + m_viewProj[3][1]);
		plane->Normalize();

		// Bottom clipping plane.
		plane = &m_planes[frustumPlane_Bottom];
		plane->Set(	
			m_viewProj[0][3] + m_viewProj[0][1],
			m_viewProj[1][3] + m_viewProj[1][1],
			m_viewProj[2][3] + m_viewProj[2][1], 
			m_viewProj[3][3] + m_viewProj[3][1]);
		plane->Normalize();

		// Near clipping plane.
		plane = &m_planes[frustumPlane_Near];
		plane->Set(m_viewProj[0][2], m_viewProj[1][2], m_viewProj[2][2], m_viewProj[3][2]);
		plane->Normalize();

		// Far clipping plane.
		plane = &m_planes[frustumPlane_Far];
		plane->Set(
			m_viewProj[0][3] - m_viewProj[0][2],
			m_viewProj[1][3] - m_viewProj[1][2],
			m_viewProj[2][3] - m_viewProj[2][2],
			m_viewProj[3][3] - m_viewProj[3][2]);
		plane->Normalize();

	}

	r_inline bool CFrustum::BoxInFrustum(const CBoundBox& box) const {
		CVec3 c((box.m_min + box.m_max) * 0.5f);
		real sizex = box.m_max.x - box.m_min.x;
		real sizey = box.m_max.y - box.m_min.y;
		real sizez = box.m_max.z - box.m_min.z;

		CVec3 corners[8] =
		{
			CVec3((c.x - sizex * 0.5f), (c.y - sizey * 0.5f), (c.z - sizez * 0.5f)),
			CVec3((c.x + sizex * 0.5f), (c.y - sizey * 0.5f), (c.z - sizez * 0.5f)),
			CVec3((c.x - sizex * 0.5f), (c.y + sizey * 0.5f), (c.z - sizez * 0.5f)),
			CVec3((c.x + sizex * 0.5f), (c.y + sizey * 0.5f), (c.z - sizez * 0.5f)),
			CVec3((c.x - sizex * 0.5f), (c.y - sizey * 0.5f), (c.z + sizez * 0.5f)),
			CVec3((c.x + sizex * 0.5f), (c.y - sizey * 0.5f), (c.z + sizez * 0.5f)),
			CVec3((c.x - sizex * 0.5f), (c.y + sizey * 0.5f), (c.z + sizez * 0.5f)),
			CVec3((c.x + sizex * 0.5f), (c.y + sizey * 0.5f), (c.z + sizez * 0.5f))
		};

		CPlane plane;
		for (int i = 0; i < 6; ++i) {
			if ( plane.Dot(m_planes[i], corners[0]) > 0.0f)
				continue;

			if ( plane.Dot(m_planes[i], corners[1]) > 0.0f)
				continue;

			if ( plane.Dot(m_planes[i], corners[2]) > 0.0f)
				continue;

			if ( plane.Dot(m_planes[i], corners[3]) > 0.0f)
				continue;

			if ( plane.Dot(m_planes[i], corners[4]) > 0.0f)
				continue;

			if ( plane.Dot(m_planes[i], corners[5]) > 0.0f)
				continue;

			if ( plane.Dot(m_planes[i], corners[6]) > 0.0f)
				continue;

			if ( plane.Dot(m_planes[i], corners[7]) > 0.0f)
				continue;

			return false;
		}

		return true;
	}

	r_inline bool CFrustum::PointInFrustum(const CVec3& point) const {
		CPlane plane;
		for (int i = 0; i < 6; ++i)	{
			if ( plane.Dot(m_planes[i], point) <= 0.0f)
				return false;
		}

		return true;
	}

	r_inline bool CFrustum::SphereInFrustum(const CBoundSphere& sphere) const {
		CPlane plane;
		for (int i = 0; i < 6; ++i)	{
			if ( plane.Dot(m_planes[i], sphere.m_center) <= -sphere.m_radius)
				return false;
		}

		return true;
	}

	r_inline void CFrustum::Draw(IRenderDriver* renderDriver) {
	}

}

#endif