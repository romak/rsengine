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

#ifndef __IARCHIVE_H__
#define __IARCHIVE_H__

namespace rengine3d {

	//! ������� ����� ��� �� �������� ����������� ������ ��� ������ � �������� � ������
	class IArchive {
	public:
		virtual ~IArchive() {};

		//! ���������� ���������� �� �����
		virtual void* GetHandle( void ) const = 0;

		//! ��������� ��� ����� ������
		virtual bool IsOpened( void ) = 0;

		//! ���������� ��� ������
		virtual string_t GetFileName( void ) = 0;

		//! ���������� ������ ���� � ������
		virtual string_t GetFullPath( void ) = 0;					

		//! ���������� ���������� ������ � ������
		virtual uint GetNumFiles( void ) = 0;				

		//! ���������� �������� ������
		virtual string_t GetDescription( void ) = 0;		

		//! ����� ����� � ������
		virtual bool FindFile( const string_t& fileName ) = 0;	

		//! ������� ����� ����� ����� ��� ������ ������ ������ � ���
		virtual IFile* NewFileObject( void ) = 0;			

		//! ��������� ����� �� ����� �����
		virtual bool Open( const string_t& archiveName ) = 0;	

		//! ��������� �����
		virtual void Close( void ) = 0;						

		//! ������� ��������� ������ ������ ������
		virtual IArchive* CreateInstance( void ) = 0;
	};

}
#endif

