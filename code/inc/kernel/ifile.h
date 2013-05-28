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

	//! Класс для работы с файлами. Используется как базовый интерфейс файловой системы движка .
	class IFile {
	public:
		virtual ~IFile(){};

		//! Получаем имя файла
		virtual string_t GetFileName( void ) = 0;

		//! Получаем полный путь к файлу
		virtual string_t GetFullPath( void ) = 0;

		//! Проверяем или файл существует
		virtual bool Exists( const string_t& fileName ) const = 0;

		//! Открыть файл по выбраному режиму
		virtual bool Open( const string_t& fileName, uint mode = fileMode_Read ) = 0;

		//! Закрыть файл
		virtual void Close( void )  = 0;

		//! Прочитать данные из файла в буффер
		virtual uint Read( void *buffer, uint len ) = 0;

		//! Записать данные буффера в файл
		virtual uint Write( void *buffer, uint len ) = 0;

		//! Возвращает длину файла
		virtual uint Length( void ) = 0;

		//! Получаем текущее смещение в файле 
		virtual uint Tell( void ) = 0;

		//! Записать буфферизированые данные в файл 
		virtual void Flush( void ) = 0;

		//! Установить позицию в файле 
		virtual bool Seek( uint offset, uint origin ) = 0;

		//! Проверить или файл открытый
		virtual bool IsOpen( void ) = 0;
	};

}
#endif

