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

#ifndef __IVAR_SYSTEM_H__
#define __IVAR_SYSTEM_H__

namespace rengine3d {

	typedef enum {
		CVAR_ALL		= -1,	  //! variable set to the all flags
		CVAR_INT		= BIT(0), //! integer variable
		CVAR_BOOL		= BIT(1), //! boolean variable
		CVAR_FLOAT		= BIT(2), //! real variable
		CVAR_STRING		= BIT(3), //! string variable
		CVAR_VEC3		= BIT(4), //! 3d vector variable

		CVAR_KERNEL		= BIT(5), //! kernel variable
		CVAR_RENDERER	= BIT(6), //! renderer variable
		CVAR_GAME		= BIT(7), //! game variable

		CVAR_STATIC		= BIT(8), //! static declared variable
		CVAR_MODIFIED	= BIT(9), //! set if variable is modified
		CVAR_READONLY	= BIT(10),//! read only variable

		CVAR_ARCHIVE	= BIT(16) //! variables saved to the config file
	}varFlags_t;

	//! class of engine variable for console
	class IVar {
	public:
		virtual ~IVar(){}

		//! return variable name
		virtual string_t GetName( void ) = 0;
		//! return variable flags
		virtual int GetFlags( void ) = 0;
		// return variable description
		virtual string_t GetDesc( void ) = 0;
		//! return string value
		virtual string_t GetString( void ) = 0;
		//! return int value
		virtual int GetInt( void ) = 0;
		//! return bool value
		virtual bool GetBool( void ) = 0;
		//! return real value
		virtual real GetFloat( void ) = 0;
		//! return vector value
		virtual CVec3 GetVec3( void ) = 0;

		//! set string value
		virtual void SetString( string_t value ) = 0;
		//! set int value
		virtual void SetInt( int value ) = 0;
		//! set bool value
		virtual void SetBool( bool value ) = 0;
		//! set real value
		virtual void SetFloat( real value ) = 0;
		//! set vector value
		virtual void SetVec3( const CVec3& value ) = 0;
		//! set variable flags
		virtual void SetFlags( const int flags ) = 0;

		//! true if modified
		virtual bool IsModified( void ) const = 0;
		//! set modified flag
		virtual void SetModified( void ) = 0;
		//! clear modified flag
		virtual void ClearModified( void ) = 0;
	};

	class IVarSystem: public ISubSystem {
	public:
		virtual ~IVarSystem(){};

		virtual void Register( IVar* var ) = 0;
		virtual IVar* CreateVar( string_t name, string_t value, int flags, string_t description ) = 0;
		virtual IVar* Find( string_t name ) = 0;

		virtual void SetString( string_t name, string_t value, int flags = 0 ) = 0;
		virtual void SetInt( string_t name, int value, int flags = 0 ) = 0;
		virtual void SetBool( string_t name, bool value, int flags = 0 ) = 0;
		virtual void SetFloat( string_t name, real value, int flags = 0 ) = 0;
		virtual void SetVec3( string_t name, const CVec3& value, int flags = 0 ) = 0;

		virtual string_t GetString( string_t name )  = 0;
		virtual int GetInt( string_t name ) = 0;
		virtual bool GetBool( string_t name ) = 0;
		virtual real GetFloat( string_t name ) = 0;
		virtual CVec3 GetVec3( string_t name ) = 0;

		virtual void Print( int flags = CVAR_ALL )  = 0;
	};

}
#endif
