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
#include "archivezip.h"
#include "filezip.h"

namespace rengine3d {

	CArchiveZip::CArchiveZip() {
		memset( &m_info, 0, sizeof( unz_global_info ) );
		m_isOpen = false;
		m_handle = NULL;
	}

	CArchiveZip::~CArchiveZip() {
		if ( this->IsOpened() ) {
			this->Close();
		}
	}

	void* CArchiveZip::GetHandle( void ) const {
		return m_handle;
	}

	bool CArchiveZip::IsOpened( void ) {
		return m_isOpen;
	}

	string_t CArchiveZip::GetFileName( void ) {
		return m_name;
	}

	string_t CArchiveZip::GetFullPath( void ) {
		return m_fullPath;
	}

	uint CArchiveZip::GetNumFiles( void )  {
		return m_info.number_entry;
	}

	string_t CArchiveZip::GetDescription( void )  {
		return "zip files reader";
	}

	bool CArchiveZip::FindFile( const string_t& fileName ) {
		if ( m_handle ) {
			int ret  = unzLocateFile( m_handle, fileName.c_str(), 0 );
			if ( ret == UNZ_OK )
				return true;
		}
		return false;
	}

	IFile* CArchiveZip::NewFileObject( void ) {
		if (m_handle)
			return new CFileZip( this->m_handle );

		return NULL;
	}

	bool CArchiveZip::Open( const string_t& archiveName ) {
		m_handle = unzOpen( archiveName.c_str() );
		if ( !m_handle )
			return false;

		int err = unzGetGlobalInfo ( m_handle, &m_info );
		if ( err != UNZ_OK ) {
			unzClose( m_handle );
			return false;
		}

		m_name		= archiveName;
		m_isOpen	= true;

		return true;
	}

	void CArchiveZip::Close( void ) {
		if ( m_handle ) {
			unzClose( m_handle );
			m_handle = NULL;
			m_isOpen = false;
		}
	}

	IArchive* CArchiveZip::CreateInstance( void ) {
		return new CArchiveZip;
	}
}
