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

#ifndef __CPLANE_H__
#define __CPLANE_H__

namespace rengine3d {

	// CPlane.
	// The plane equation is: ax + by + cz + d = 0.
	// The plane's normal (a, b, c) in stored in a CVec3 so that functionality from the CVec3 class can be used.

	class CPlane {
	public:
		CPlane();
		CPlane(real a, real b, real c, real d);
		CPlane(const CVec3& normal, real dist);
		~CPlane(){};

		void Set(real a, real b, real c, real d);
		
		void MakeFromPoints(const CVec3& p1, const CVec3& p2, const CVec3& p3);
		void MakeFormPointNormal(const CVec3& p, const CVec3& normal);

		void Normalize(void);

		// if > 0 point in front of the plane
		// if < 0 point in back of the plane
		// if = 0 point on the plane
		real Dot(const CPlane& plane, const CVec3& p);
		real Dot(const CVec3& p);

		real DistanceToPlane (const CVec3& point) const;

		//calculates the intersection point of a line with this plane. Returns false if there is no intersection
		bool FindLineSegIntersection (const CVec3& start, const CVec3& end, CVec3* intsect);
		bool FindRayIntersection (const CVec3& start, const CVec3& direction, CVec3* intsect);
	public:
		CVec3	m_normal;
		real	m_distance;
	};

	r_inline CPlane::CPlane() {
	}

	r_inline CPlane::CPlane(real a, real b, real c, real d): m_normal(a,b,c), m_distance(d) {
	}

	r_inline CPlane::CPlane(const CVec3& normal, real dist): m_normal(normal), m_distance(dist) {
	}

	r_inline void CPlane::Set(real a, real b, real c, real d) {
		m_normal.Set(a,b,c);
		m_distance = d;
	}

	r_inline void CPlane::MakeFromPoints(const CVec3& p1, const CVec3& p2, const CVec3& p3) {
		m_normal.Cross(p2-p1, p3-p1);
		m_distance = -m_normal.Dot(p1); 
		this->Normalize();
	}

	r_inline void CPlane::MakeFormPointNormal(const CVec3& p, const CVec3& normal) {
		this->Set(normal.x, normal.y, normal.z, -normal.Dot(p));
		this->Normalize();
	}

	r_inline void CPlane::Normalize(void) {
		real len	= 1.0f / m_normal.Len();
		m_normal	*= len;
		m_distance	*= len;
	}

	r_inline real CPlane::Dot(const CPlane& plane, const CVec3& p) {
		return plane.m_normal.Dot(p) + plane.m_distance;
	}

	r_inline real CPlane::Dot(const CVec3& p) {
		return this->m_normal.Dot(p) + this->m_distance;
	}

	r_inline real CPlane::DistanceToPlane (const CVec3& point) const {
		return m_normal.x * point.x + m_normal.y * point.y + m_normal.z * point.z + m_distance;
	}

	r_inline bool CPlane::FindLineSegIntersection (const CVec3& start, const CVec3& end, CVec3* intsect) {
		real dist1 = DistanceToPlane(start);
		real dist2 = DistanceToPlane(end);

		if ( (dist1 < 0 && dist2 < 0) || (dist1 >= 0 && dist2 >= 0) )
			return false;

		real t = (-dist1) / (dist2-dist1);
		*intsect = Interpolate( start, end, t );

		return true;
	}

	r_inline bool CPlane::FindRayIntersection (const CVec3& start, const CVec3& direction, CVec3* intsect) {
		real dot = m_normal.Dot (direction);
		if (dot == 0.0f)
			return false;

		*intsect = start - (direction * (DistanceToPlane (start) / dot));
		return true;
	}

}

#endif