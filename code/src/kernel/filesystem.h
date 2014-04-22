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

#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__

namespace rengine3d {

	typedef std::map<string_t, string_t>	assignMap_t;	
	typedef std::vector<IArchive*>			archives_t;
	typedef std::vector<IArchive*>			archiveFactory_t;

	typedef std::vector<IFile*>				filesList_t;

	class CFileSystem: public IFileSystem {
	public:
		CFileSystem();
		virtual ~CFileSystem();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual bool IsInitialized(void) { return m_initialized; };

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		virtual IFile* OpenFile( const string_t& relativePath, uint mode = fileMode_Read );
		virtual void CloseFile( IFile* file );
		virtual bool FileExists( const string_t& fileName ) ;
		virtual string_t GetWorkingDir( void );
		virtual bool ChangeDir( const string_t& dir );
		virtual void SetAlias( const string_t& name, const string_t& path );
		virtual string_t GetAlias( const string_t& name );
		virtual string_t GetFilePath( const string_t& fileName );
		virtual string_t GetFileName( const string_t& fileName );
		virtual string_t GetFileNameNoExt( const string_t& fileName );
		virtual string_t GetFileExtension( const string_t& fileName );
		virtual string_t GetLowerCaseFileExtension(const string_t& fileName);
		virtual string_t ConvertPathToWin( const string_t& path );
		virtual string_t ConvertPathToUnix( const string_t& path );
		virtual CFileList* ListFiles( const string_t& path, const string_t& ext );
		virtual IXML* CreateXML(void);
		virtual void RegisterArchiveReader( IArchive* archive );

		virtual string_t GetClassName() { return "CFileSystem"; };
	private:
		assignMap_t			m_assigns;
		archives_t			m_archives;
		archiveFactory_t	m_archiveFactory;
		filesList_t			m_files;

	};

}
#endif
