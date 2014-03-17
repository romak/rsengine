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

#ifndef __CARGS_H__
#define __CARGS_H__

namespace rengine3d {

	const int MAX_COMMAND_ARGS		= 32;
	const int MAX_COMMAND_STRING	= 2 * 256;

	//! arguments
	class CArgs {
	public:
		//! constructor
		CArgs( void ) { m_argc = 0; };
		CArgs( const char* text );

		//! return number of arguments
		int Argc( void ) const { return m_argc; };
		//! return argument by index
		const char* Argv( int arg ) const { return ( arg >= 0 && arg < m_argc ) ? m_argv[arg] : ""; }
		//! clear args
		void Clear( void ) { m_argc = 0; };
	private:
		int		m_argc;						//! number of arguments
		char*	m_argv[MAX_COMMAND_ARGS];	//! array with arguments
		char	m_str[MAX_COMMAND_STRING];	//! for store input arguments
	};

	inline CArgs::CArgs( const char* text ) {
		char seps[]   = " ,\t\n";
		char *token;
		char *next_token1 = NULL;

		strcpy_s( m_str, text );

		m_argc = 0;
		token = strtok_s( m_str, seps, &next_token1 );
		while( token != NULL ) {
			if ( m_argc < MAX_COMMAND_ARGS ) {
				m_argv[m_argc] = token;
			}
			m_argc++;
			token = strtok_s( NULL, seps, &next_token1 );
		}
	}

}

#endif
