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

#ifndef __ARCHIVE_ZIP_H__
#define __ARCHIVE_ZIP_H__

namespace rengine3d {

	class CArchiveZip: public IArchive {
	public:
		CArchiveZip();
		virtual ~CArchiveZip();

		virtual void* GetHandle( void ) const;
		virtual bool IsOpened( void );
		virtual string_t GetFileName( void );
		virtual string_t GetFullPath( void );					
		virtual uint GetNumFiles( void );				
		virtual string_t GetDescription( void );
		virtual bool FindFile( const string_t& fileName );
		virtual IFile* NewFileObject( void );
		virtual bool Open( const string_t& archiveName );
		virtual void Close( void );
		virtual IArchive* CreateInstance( void );
	protected:
		unz_global_info	m_info;
		bool			m_isOpen;
		string_t		m_name;
		string_t		m_fullPath;
		void*			m_handle;
	};

}

#endif
