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

#ifndef __FILE_H__
#define __FILE_H__

namespace rengine3d {

	// Класс для работы с файлами
	class CFile: public IFile {
	public:
		CFile();
		virtual ~CFile();

		virtual void Init(void);
		virtual void Shutdown(void);

		virtual string_t GetFileName( void );
		virtual string_t GetFullPath( void );
		virtual bool Exists( const string_t& fileName ) const;
		virtual bool Open( const string_t& fileName, uint mode = fileMode_Read );
		virtual void Close( void );
		virtual uint Read( void *buffer, uint len );
		virtual uint Write( void *buffer, uint len );
		virtual uint Length( void );
		virtual uint Tell( void );
		virtual void Flush( void );
		virtual bool Seek( uint offset, uint origin );
		virtual bool IsOpen( void );

		virtual string_t GetClassName() { return "CFile"; };
	private:
		FILE*		m_handle;
		string_t	m_fileName;
		string_t	m_path;
		bool		m_isOpen;
		int			m_mode;
		uint		m_fileSize;
	};

}

#endif

