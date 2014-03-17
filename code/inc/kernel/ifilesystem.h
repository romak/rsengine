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

#ifndef __IFILESYSTEM_H__
#define __IFILESYSTEM_H__

namespace rengine3d {

	typedef std::vector<string_t> fileList_t;

	class CFileList {
	public:
		string_t			GetFile( uint index )	{ return m_list[index]; };
		string_t			GetPath( void )			{ return m_path; };
		const fileList_t&	GetList( void )			{ return m_list; };
		uint				GetNumFiles( void )		{ return (uint)m_list.size();};
	public:
		string_t	m_path;
		fileList_t	m_list;
	};

	//! ����� ��� ������ � �������� ��������, �������� � �������.
	class IFileSystem: public ISubSystem  {
	public:
		virtual ~IFileSystem() {};

		//! ������� ����
		virtual IFile* OpenFile( const string_t& relativePath, uint mode = fileMode_Read ) = 0;

		//! ������� ����
		virtual void CloseFile( IFile* file ) = 0;

		//! ��������� ��� ���� ����������
		virtual bool FileExists( const string_t& fileName )  = 0;

		//! ���������� ������� ������� ������
		virtual string_t GetWorkingDir( void ) = 0;

		//! ���������� ������� �������
		virtual bool ChangeDir( const string_t& dir ) = 0;

		//! ���������� �����
		virtual void SetAlias( const string_t& name, const string_t& path ) = 0;

		//! �������� ����� �� �����
		virtual string_t GetAlias( const string_t& name ) = 0;

		//! ���������� ���� � �����
		virtual string_t GetFilePath( const string_t& fileName ) = 0;

		//! ���������� ��� �����
		virtual string_t GetFileName( const string_t& fileName ) = 0;

		//! ���������� ��� ����� ��� ����������
		virtual string_t GetFileNameNoExt( const string_t& fileName ) = 0;

		//! ���������� ���������� �����
		virtual string_t GetFileExtension( const string_t& fileName ) = 0;

		//! ������������ ���� � ����� ��������
		virtual string_t ConvertPathToWin( const string_t& path ) = 0;

		//! ������������ ���� � ����� �����
		virtual string_t ConvertPathToUnix( const string_t& path ) = 0;

		virtual string_t GetLowerCaseFileExtension(const string_t& fileName) = 0;

		//! ���������� ������ ������ � �������� �� ���������� 
		virtual CFileList* ListFiles( const string_t& path, const string_t& ext ) = 0;

		virtual IXML* CreateXML(void) = 0;

		//! ��������� ����� ��� ������ �������� ������� � �������� (� ������� .zip, .rar ...)
		virtual void RegisterArchiveReader( IArchive* archive ) = 0;
	};

}
#endif
