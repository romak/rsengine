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

#ifndef __IFILE_H__
#define __IFILE_H__

namespace rengine3d {

	typedef enum {
		fileOrigin_SeekCur	= 0,
		fileOrigin_SeekEnd	= 1,
		fileOrigin_SeekSet	= 2
	} fileOrigin_t;

	typedef enum {
		fileMode_Read		= 0,
		fileMode_Write		= 1,
		fileMode_Append		= 2
	} fileMode_t;

	//! ����� ��� ������ � �������. ������������ ��� ������� ��������� �������� ������� ������ .
	class IFile {
	public:
		virtual ~IFile(){};

		//! �������� ��� �����
		virtual string_t GetFileName( void ) = 0;

		//! �������� ������ ���� � �����
		virtual string_t GetFullPath( void ) = 0;

		//! ��������� ��� ���� ����������
		virtual bool Exists( const string_t& fileName ) const = 0;

		//! ������� ���� �� ��������� ������
		virtual bool Open( const string_t& fileName, uint mode = fileMode_Read ) = 0;

		//! ������� ����
		virtual void Close( void )  = 0;

		//! ��������� ������ �� ����� � ������
		virtual uint Read( void *buffer, uint len ) = 0;

		//! �������� ������ ������� � ����
		virtual uint Write( void *buffer, uint len ) = 0;

		//! ���������� ����� �����
		virtual uint Length( void ) = 0;

		//! �������� ������� �������� � ����� 
		virtual uint Tell( void ) = 0;

		//! �������� ���������������� ������ � ���� 
		virtual void Flush( void ) = 0;

		//! ���������� ������� � ����� 
		virtual bool Seek( uint offset, uint origin ) = 0;

		//! ��������� ��� ���� ��������
		virtual bool IsOpen( void ) = 0;
	};

}
#endif

