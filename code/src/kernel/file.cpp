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
#include "file.h"

namespace rengine3d {

	CFile::CFile(): m_handle(NULL), m_isOpen(false), m_mode(fileMode_Read), m_fileSize(0) {
	}

	CFile::~CFile() {
		if ( this->IsOpen() ) {
			this->Close();
		}
	}

	void CFile::Init(void) {
	}

	void CFile::Shutdown(void) {
	}

	string_t CFile::GetFileName( void ) {
		return m_fileName;
	}

	string_t CFile::GetFullPath( void ) {
		return m_path;
	}

	bool CFile::Exists( const string_t& fileName ) const {
		FILE *f;

		f = fopen( fileName.c_str(), "rb" );
		if (f) {
			fclose( f );
			return true;
		}

		return false;
	}

	bool CFile::Open( const string_t& fileName, uint mode ) {
		m_fileName	= fileName;
		m_isOpen	= true;

		switch ( mode ) {
		case fileMode_Read:
			m_handle = fopen(fileName.c_str(), "rb");
			break;
		case fileMode_Write:
			m_handle = fopen(fileName.c_str(), "w");
			break;
		case fileMode_Append:
			m_handle = fopen(fileName.c_str(), "a");
			break;
		};

		if ( m_handle ) {
			fseek( m_handle, 0, SEEK_END );
			m_fileSize = ftell( m_handle );
			fseek( m_handle, 0, SEEK_SET );
		} else {
			m_isOpen = false;
		}

		return m_handle != NULL;
	}

	void CFile::Close( void ) {
		if ( m_handle )
			fclose( m_handle );
	}

	uint CFile::Read( void *buffer, uint len ) {
		if ( !m_isOpen )
			return 0;

		return (uint)fread( buffer, len, 1, m_handle );
	}

	uint CFile::Write( void *buffer, uint len ) {
		if ( !m_isOpen )
			return 0;

		return (uint)fwrite( buffer, 1, len, m_handle );
	}

	uint CFile::Length( void ) {
		return m_fileSize;
	}

	uint CFile::Tell( void ) {
		if ( m_handle )
			return ftell( m_handle );

		return 0;
	}

	void CFile::Flush( void ) {
		if ( m_handle )
			fflush( m_handle );
	}

	bool CFile::Seek( uint offset, uint origin ) {
		if ( !m_isOpen )
			return false;

		int mode = SEEK_CUR;
		switch ( origin ) {
		case fileOrigin_SeekCur:
			mode = SEEK_CUR;
			break;
		case fileOrigin_SeekSet:
			mode = SEEK_SET;
			break;
		case fileOrigin_SeekEnd:
			mode = SEEK_END;
			break;
		}
		return fseek( m_handle, offset, mode ) == 0;
	}

	bool CFile::IsOpen( void ) {
		return m_isOpen;
	}
}
