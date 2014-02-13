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
#include "file.h"
#include "filesystem.h"
//#include "xml.h"

#include <direct.h>
#include <io.h>

namespace rengine3d {

#if PLATFORM == PLATFORM_WIN32
#	include <windows.h>
	CHAR wide_to_narrow(WCHAR w);
#endif

	CFileSystem::CFileSystem() {
		m_initialized = false;
	}

	CFileSystem::~CFileSystem() {
		this->Shutdown();
	}

	string_t CFileSystem::GetName(void) {
		return "CFileSystem";
	}

	string_t CFileSystem::GetDescription(void) {
		return "File system";
	}

	string_t CFileSystem::GetVersion(void) {
		return "0.0.1";
	}

	bool CFileSystem::Init(void) {

		Log("\tInitializing FileSystem...\n");

#if PLATFORM == PLATFORM_WIN32
		WCHAR	buf[256];
		WCHAR	c, *p;
		size_t	i;

		HMODULE hMod	= GetModuleHandle( NULL );
		DWORD	res		= GetModuleFileNameW( hMod, buf, sizeof( buf ) );

		for ( i = 0; i < 3; i++ ) {
			p = wcsrchr( buf, '\\' );
			p[0] = 0;
		}

		// convert backslashes to slashes
		p = buf;
		while ( ( c = *p ) ) {
			if ( c == '\\' ) *p = '/';
			p++;
		}
		wcscat( buf, L"/" );

		std::wstring wstr = _wcslwr( buf );
		std::string dest;
		dest.resize(wstr.length());
		std::transform(wstr.begin(), wstr.end(), dest.begin(), wide_to_narrow);

		SetAlias( "home", dest );
		string_t home = GetAlias( "home" );
		SetAlias( "bin", home+"bin/win32/" );
		SetAlias( "bin", home+"data/" );
#endif
		m_initialized = true;

		return m_initialized;
	}

	void CFileSystem::Shutdown(void) {
		size_t i;

		Log("\tShutdown FileSystem...\n");

		for ( i = 0; i < m_archives.size(); i++ ) 
			SafeDelete(m_archives[i]);

		for ( i = 0; i < m_archiveFactory.size(); i++ )
			SafeDelete(m_archiveFactory[i]);

		m_archives.clear();
		m_archiveFactory.clear();

		m_assigns.clear();

		m_initialized = false;
	}

	IFile* CFileSystem::OpenFile( const string_t& relativePath, uint mode ) {
		string_t				fullPath;
		assignMap_t::iterator	it;
		IFile*					file;
	
	#if PLATFORM == PLATFORM_WIN32
		file = new CFile;
	#elif defined(PLATFORM_LINUX)
	#else
	#endif

		// first try open file by OS path
		if ( file->Open( relativePath, mode ) )
			return file;

		// try open file from assign map
		for ( it = m_assigns.begin(); it != m_assigns.end(); ++it ) {
			fullPath = it->second.c_str();
			fullPath += relativePath;
			if ( file->Open( fullPath.c_str(), mode ) ) {
				return file;
			} 
		}

		SafeDelete(file);

		for ( size_t i = 0; i < m_archives.size(); i++ ) {
			if ( m_archives[i]->FindFile( relativePath ) ) {
				file = m_archives[i]->NewFileObject();
				if ( file->Open( relativePath ) ) {
					return file;
				} else {
					SafeDelete(file);
				}
			}
		}

		return NULL;
	}

	void CFileSystem::CloseFile( IFile* file ) {
		if ( file ) {
			file->Close();
			SafeDelete(file);
		}
	}

	bool CFileSystem::FileExists( const string_t& fileName ) {
		IFile* file = this->OpenFile( fileName, fileMode_Read );
		if ( file ) { 
			file->Close();
			SafeDelete(file);
			return true; 
		} else 
			return false;
	}

	string_t CFileSystem::GetWorkingDir( void ) {
		return GetAlias( "home" );
	}

	bool CFileSystem::ChangeDir( const string_t& dir ) {
		return ( _chdir( dir.c_str() ) != -1 );
	}

	void CFileSystem::SetAlias( const string_t& name, const string_t& path ) {
		assignMap_t::iterator it = m_assigns.find( name );

		if ( it != m_assigns.end() ) 
			m_assigns.erase(it);

		m_assigns.insert( assignMap_t::value_type( name, path ) );
	}

	string_t CFileSystem::GetAlias( const string_t& name ) {
		assignMap_t::iterator it = m_assigns.find( name );

		if ( it == m_assigns.end() ) {
			return NULL;
		}

		return it->second;
	}

	string_t CFileSystem::GetFilePath( const string_t& fileName ) {
		string_t::size_type slash1 = fileName.find_last_of( '/' );
		string_t::size_type slash2 = fileName.find_last_of( '\\' );

		if ( slash1 == std::string::npos ) {
			if ( slash2 == std::string::npos) 
				return "";
			return std::string( fileName, 0, slash2 ).c_str();
		}
		if ( slash2 == std::string::npos) 
			return std::string( fileName, 0, slash1 ).c_str();

		return std::string( fileName, 0, slash1>slash2 ?  slash1 : slash2 ).c_str();
	}

	string_t CFileSystem::GetFileName( const string_t& fileName ) {
		string_t::size_type slash1 = fileName.find_last_of( '/' );
		string_t::size_type slash2 = fileName.find_last_of( '\\' );

		if ( slash1 == string_t::npos ) {
			if ( slash2 == string_t::npos) 
				return fileName;
			return string_t( fileName.begin() + slash2 + 1, fileName.end() );
		}

		if ( slash2 == string_t::npos) 
			return string_t( fileName.begin() + slash1 + 1, fileName.end() );

		return string_t( fileName.begin() + ( slash1 > slash2 ? slash1 : slash2 ) + 1, fileName.end() );
	}

	string_t CFileSystem::GetFileNameNoExt( const string_t& fileName ) {
		string_t::size_type dot = fileName.find_last_of( '.' );
		string_t::size_type slash1 = fileName.find_last_of( '/' );
		string_t::size_type slash2 = fileName.find_last_of( '\\' );

		if ( slash1 == string_t::npos ) {
			if ( slash2 == string_t::npos) 
				return fileName;
			return string_t( fileName.begin() + slash2 + 1, fileName.end() );
		}

		if ( slash2 == string_t::npos) 
			return string_t( fileName.begin() + slash1 + 1 , fileName.end()- ( dot - slash1 - 2)  );

		return string_t( fileName.begin() + ( slash1 > slash2 ? slash1 : slash2 ) + 1, fileName.end() - dot );
	}

	string_t CFileSystem::GetFileExtension( const string_t& fileName ) {
		string_t::size_type dot = fileName.find_last_of( '.' );

		if ( dot == std::string::npos) 
			return string_t( "" );

		return string_t( fileName.begin() + dot + 1, fileName.end() );
	}

	string_t CFileSystem::GetLowerCaseFileExtension(const string_t& fileName) {
		string_t ext = this->GetFileExtension( fileName );

		for( string_t::iterator itr = ext.begin(); itr != ext.end(); ++itr ) {
			*itr = tolower(*itr);
		}

		return ext;
	}

	string_t CFileSystem::ConvertPathToWin( const string_t& path ) {
		string_t newPath( path );

		string_t::size_type slash = 0;
		while( ( slash =newPath.find_first_of( '/', slash ) ) != string_t::npos) {
			newPath[slash] = '\\';
		}
		return newPath;
	}

	string_t CFileSystem::ConvertPathToUnix( const string_t& path ) {
		string_t newPath( path );

		string_t::size_type slash = 0;
		while( ( slash = newPath.find_first_of( '\\', slash ) ) != string_t::npos) {
			newPath[slash] = '/';
		}

		return newPath;
	}

	CFileList* CFileSystem::ListFiles( const string_t& path, const string_t& ext ) {
		static CFileList	fileList;
		long				handle, res;
		struct _finddata_t	findData;
		string_t			str;

		fileList.m_list.clear();

		str = path;
		str += "\\";
		str += ext;
		fileList.m_path = path;

		memset( &findData, 0, sizeof( findData ) );
		findData.attrib	=_A_SUBDIR;
		findData.size	= sizeof( findData );

		handle = _findfirst( str.c_str(), &findData );
		res = 0;

		while ( handle != -1 && res != -1 ) {
			if( !( findData.attrib & _A_SUBDIR ) ) {
				fileList.m_list.push_back( findData.name);
			}
			res = _findnext( handle, &findData );
		}

		if( handle != -1 ) {
			_findclose( handle );
		}

		// TODO: try find files in packs ???

		return &fileList;
	}

	IXML* CFileSystem::CreateXML(void) {
	//	return new CXML(this);
		return NULL;
	}

	void CFileSystem::RegisterArchiveReader( IArchive* archive ) {
		for ( size_t i = 0; i < m_archiveFactory.size(); i++ ) {
			if ( archive == m_archiveFactory[i] )
				return;
		}

		m_archiveFactory.push_back( archive );
	}

	// --- Help-in functions ---
	CHAR wide_to_narrow(WCHAR w){
		return CHAR(w);
	}
}
