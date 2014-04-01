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

#ifndef __IGEOMETRY_H__
#define __IGEOMETRY_H__

namespace rengine3d {

	class IGeometry {
	public:
		IGeometry(const string_t& name);
		virtual ~IGeometry();

		void Clear(void);
		void ClearIndices(void);
		void ClearVertices(void);
		void ClearNormals(void);
		void ClearTangents(void);
		void ClearTexCoords(void);
		void ClearColors(void);

		void*  AllocIndices(uint size, indicesType_t type);
		CVec4* AllocColors(uint size);
		CVec3* AllocVertices(uint size);
		CVec3* AllocNormals(uint size);
		CVec3* AllocTangents(uint size);
		CVec2* AllocTexCoords(uint size);

		void*	GetIndices(void)	{ return m_indices; }
		CVec4*	GetColors(void)		{ return m_colors; }
		CVec3*	GetVertices(void)	{ return m_vertices; }
		CVec3*	GetNormals(void)	{ return m_normals; }
		CVec3*	GetTangents(void)	{ return m_tangents; }
		CVec2*	GetTexCoords(void)	{ return m_texCoords; }

		indicesType_t GetIndicesType() {return m_indicesType; }

		void ComputeCenter(void);
		void ComputeFaceNormals(void);
		void ComputeVertexNormals(void);
		void ComputeMorphNormals(void);
		void ComputeTangents(void);
		void ComputeBoundingBox(void);
		void MergeVertices(void);
	public:
		string_t		m_name;
		uint			m_id;

		indicesType_t	m_indicesType;

		uint			m_indicesSize;
		uint			m_verticesSize;
		uint			m_normalsSize;
		uint			m_tangentsSize;
		uint			m_texCoordsSize;
		uint			m_colorsSize;

		CVec4*			m_colors;
		CVec3*			m_vertices;
		CVec3*			m_normals;
		CVec3*			m_tangents;
		CVec2*			m_texCoords;
		void*			m_indices;

		bool			m_hasTangents;
		CBoundBox		m_boundBox;
	};

	r_inline IGeometry::IGeometry(const string_t& name): m_name(name) {
		m_id				= MakeCRC(name.c_str());

		m_hasTangents		= false;
		m_indicesType		= indicesType_uint;

		m_indicesSize		= 0;
		m_verticesSize		= 0;
		m_normalsSize		= 0;
		m_tangentsSize		= 0;
		m_texCoordsSize		= 0;
		m_colorsSize		= 0;

		m_colors			= NULL;
		m_vertices			= NULL;
		m_normals			= NULL;
		m_tangents			= NULL;
		m_texCoords			= NULL;
		m_indices			= NULL;
	}

	r_inline IGeometry::~IGeometry() {
		this->Clear();
	}

	r_inline void IGeometry::Clear(void) {
		ClearIndices();
		ClearVertices();
		ClearNormals();
		ClearTangents();
		ClearTexCoords();
		ClearColors();
	}

	r_inline void IGeometry::ClearIndices(void) {
		m_indicesSize = 0;
		SafeArrayDelete(m_indices);
	}

	r_inline void IGeometry::ClearVertices(void) {
		m_verticesSize = 0;
		SafeArrayDelete(m_vertices);
	}

	r_inline void IGeometry::ClearNormals(void) {
		m_normalsSize = 0;
		SafeArrayDelete(m_normals);
	}

	r_inline void IGeometry::ClearTangents(void) {
		m_tangentsSize = 0;
		SafeArrayDelete(m_tangents);
	}

	r_inline void IGeometry::ClearTexCoords(void) {
		m_texCoordsSize = 0;
		SafeArrayDelete(m_texCoords);
	}

	r_inline void IGeometry::ClearColors(void) {
		m_colorsSize = 0;
		SafeArrayDelete(m_indices);
	}

	r_inline void* IGeometry::AllocIndices(uint size, indicesType_t type) {
		ClearIndices();

		if(size == 0)
			return NULL;

		m_indicesType = type;
		m_indicesSize = size;

		switch(type)
		{
		default:
		case indicesType_uint:
			m_indices =  new uint[sizeof(uint)*size];
			break;
		case indicesType_ushort:
			m_indices =  new ushort[sizeof(ushort)*size];
			break;
		}

		return m_indices;
	}

	r_inline CVec4* IGeometry::AllocColors(uint size) {
		ClearColors();
	}

	r_inline CVec3* IGeometry::AllocVertices(uint size) {
		ClearVertices();

		if(size == 0)
			return NULL;

		m_verticesSize = size;
		m_vertices = new CVec3[size];

		return m_vertices;
	}

	r_inline CVec3* IGeometry::AllocNormals(uint size) {
		ClearNormals();

		m_normalsSize = size;
		m_normals = new CVec3[size];

		return m_normals;
	}

	r_inline CVec3* IGeometry::AllocTangents(uint size){
		ClearTangents();

		if(size == 0)
			return NULL;

		m_tangentsSize = size;
		m_tangents = new CVec3[size];

		return m_tangents;
	}

	r_inline CVec2* IGeometry::AllocTexCoords(uint size) {
		ClearTexCoords();

		if(size == 0)
			return NULL;

		m_texCoordsSize = size;
		m_texCoords = new CVec2[size];

		return m_texCoords;
	}

	r_inline void IGeometry::ComputeCenter(void) {
	}

	r_inline void IGeometry::ComputeFaceNormals(void) {
	}

	r_inline void IGeometry::ComputeVertexNormals(void) {
	}

	r_inline void IGeometry::ComputeMorphNormals(void) {
	}

	r_inline void IGeometry::ComputeTangents(void) {
	}

	r_inline void IGeometry::ComputeBoundingBox(void) {
	}

	r_inline void IGeometry::MergeVertices(void) {
	}

}

#endif
