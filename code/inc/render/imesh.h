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

#ifndef __IMESH_H__
#define __IMESH_H__

namespace rengine3d {

	class ISubMesh {
	public:
		ISubMesh();
		virtual ~ISubMesh();

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

	protected:
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

		CBoundBox		m_boundBox;
	};

	r_inline ISubMesh::ISubMesh():m_colors(NULL),m_vertices(NULL),m_normals(NULL),m_tangents(NULL),m_texCoords(NULL),m_indices(NULL) {
		m_indicesSize = 0; m_verticesSize = 0; m_normalsSize = 0; m_tangentsSize = 0; m_texCoordsSize = 0; m_colorsSize = 0;
	}

	r_inline ISubMesh::~ISubMesh() {
		Clear();
	}

	r_inline void ISubMesh::Clear(void) {
		ClearIndices();
		ClearVertices();
		ClearNormals();
		ClearTangents();
		ClearTexCoords();
		ClearColors();
	}

	r_inline void ISubMesh::ClearIndices(void) {
		m_indicesSize = 0;
		SafeArrayDelete(m_indices);
	}

	r_inline void ISubMesh::ClearVertices(void) {
		m_verticesSize = 0;
		SafeArrayDelete(m_vertices);
	}

	r_inline void ISubMesh::ClearNormals(void) {
		m_normalsSize = 0;
		SafeArrayDelete(m_normals);
	}

	r_inline void ISubMesh::ClearTangents(void) {
		m_tangentsSize = 0;
		SafeArrayDelete(m_tangents);
	}

	r_inline void ISubMesh::ClearTexCoords(void) {
		m_texCoordsSize = 0;
		SafeArrayDelete(m_texCoords);
	}

	r_inline void ISubMesh::ClearColors(void) {
		m_colorsSize = 0;
		SafeArrayDelete(m_indices);
	}

	r_inline void* ISubMesh::AllocIndices(uint size, indicesType_t type) {
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

	r_inline CVec4* ISubMesh::AllocColors(uint size) {
		ClearColors();
	}

	r_inline CVec3* ISubMesh::AllocVertices(uint size) {
		ClearVertices();

		if(size == 0)
			return NULL;

		m_verticesSize = size;
		m_vertices = new CVec3[size];

		return m_vertices;
	}

	r_inline CVec3* ISubMesh::AllocNormals(uint size) {
		ClearNormals();

		m_normalsSize = size;
		m_normals = new CVec3[size];

		return m_normals;
	}

	r_inline CVec3* ISubMesh::AllocTangents(uint size){
		ClearTangents();

		if(size == 0)
			return NULL;

		m_tangentsSize = size;
		m_tangents = new CVec3[size];

		return m_tangents;
	}

	r_inline CVec2* ISubMesh::AllocTexCoords(uint size) {
		ClearTexCoords();

		if(size == 0)
			return NULL;

		m_texCoordsSize = size;
		m_texCoords = new CVec2[size];

		return m_texCoords;
	}


	class IMesh {
	public:
		IMesh();
		virtual ~IMesh();

		void ClearSubMeshes(void);
		void Clear(void);

		ISubMesh* AllocSubMeshes(uint size);

		uint GetNumSubMeshes(void)		{ return m_numSubMeshes; }
		ISubMesh* GetSubMeshes(void)	{ return m_subMeshes; }

	protected:
		uint		m_numSubMeshes;
		ISubMesh*	m_subMeshes;

		CBoundBox m_boundgBox;
	};


	r_inline IMesh::IMesh(): m_numSubMeshes(0), m_subMeshes(NULL) {

	}

	r_inline IMesh::~IMesh() {
		Clear();
	}

	r_inline void IMesh::Clear(void) {
		ClearSubMeshes();
	}

	r_inline void IMesh::ClearSubMeshes(void) {
		m_numSubMeshes = 0;
		SafeArrayDelete(m_subMeshes);

	}

	r_inline ISubMesh* IMesh::AllocSubMeshes(uint size) {
		ClearSubMeshes();

		if(size == 0)
			return NULL;

		m_numSubMeshes	= size;
		m_subMeshes		= new ISubMesh[size];
		return m_subMeshes;
	}

}



#endif


