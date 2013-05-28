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

	//! Базовый класс для от которого порождаются классы для работы с архивами в движке
	class IArchive {
	public:
		virtual ~IArchive() {};

		//! Возвращает дескриптор на архив
		virtual void* GetHandle( void ) const = 0;

		//! Проверяет или архив открыт
		virtual bool IsOpened( void ) = 0;

		//! Возвращает имя архива
		virtual string_t GetFileName( void ) = 0;

		//! Возвращает полный путь к архиву
		virtual string_t GetFullPath( void ) = 0;					

		//! Возвращает количество файлов в архиве
		virtual uint GetNumFiles( void ) = 0;				

		//! Возвращает описание архива
		virtual string_t GetDescription( void ) = 0;		

		//! Поиск файла в архиве
		virtual bool FindFile( const string_t& fileName ) = 0;	

		//! Создает новый класс файла для работы внутри архива с ним
		virtual IFile* NewFileObject( void ) = 0;			

		//! Открывает архив по имени файла
		virtual bool Open( const string_t& archiveName ) = 0;	

		//! Закрывает архив
		virtual void Close( void ) = 0;						

		//! Создает экземпляр своего класса архива
		virtual IArchive* CreateInstance( void ) = 0;
	};

}
#endif

