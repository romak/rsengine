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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "unzip/unzip.h"
#include "filezip.h"

namespace rengine3d {

	CFileZip::CFileZip( void* zipHandle ): IFile( ) {
		m_zipFile	= zipHandle;
		m_zipInfo	= NULL;
		m_isOpen	= false;
		m_mode		= fileMode_Read;
	}

	CFileZip::~CFileZip() {
		if ( this->IsOpen() ) {
			this->Close();
		}
	}

	void CFileZip::Init(void) {
	}

	void CFileZip::Shutdown(void) {
	}

	string_t CFileZip::GetFileName( void ) {
		return m_fileName; 
	}

	string_t CFileZip::GetFullPath( void ) {
		return m_path; 
	}

	bool CFileZip::Exists( const string_t& fileName ) const {
		return false;
	}

	bool CFileZip::Open( const string_t& fileName, uint mode ) {
		if ( m_isOpen )return 0;

		static unz_file_info fi;

		int ret = unzLocateFile( m_zipFile, fileName.c_str(), 1 );

		if ( ret == UNZ_OK ) {
			unzOpenCurrentFile( m_zipFile );
			unzGetCurrentFileInfo( m_zipFile, &fi, (char*)fileName.c_str(), 0, NULL, 0, NULL, 0 );
			m_zipInfo	= &fi;
			m_fileName	= fileName;
			m_isOpen	= true;
			return true;
		}

		m_isOpen = false;

		return false;
	}

	void CFileZip::Close( void )  {
		if ( m_zipFile ) {
			unzCloseCurrentFile( m_zipFile );
			this->m_zipInfo	= NULL;
			this->m_isOpen	= false;
		}
	}

	uint CFileZip::Read( void *buffer, uint len ) {
		if ( !m_isOpen )
			return 0;

		return unzReadCurrentFile( this->m_zipFile, buffer, len );
	}

	uint CFileZip::Write( void *buffer, uint len ) {
		return 0;
	}

	uint CFileZip::Length( void ) {
		if ( !m_isOpen )
			return 0;

		unz_file_info* fi = (unz_file_info*)m_zipInfo;
		return fi->uncompressed_size;
	}

	uint CFileZip::Tell( void ) {
		if ( !m_isOpen )
			return 0;

		return unztell( this->m_zipFile );
	}

	void CFileZip::Flush( void ) {
	}

	bool CFileZip::Seek( uint offset, uint origin ) {
		return false;
	}

	bool CFileZip::IsOpen( void ) {
		return m_isOpen;
	}

}
