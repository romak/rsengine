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

#ifndef __ICMD_SYSTEM_H__
#define __ICMD_SYSTEM_H__

namespace rengine3d {

	//! command flags
	typedef enum {
		cmdFlags_All		= -1,
		cmdFlags_Kernel		= BIT(0),
		cmdFlags_Render		= BIT(1),
		cmdFlags_Game		= BIT(2),
		cmdFlags_User		= BIT(2),
	} cmdFlags_t;

	typedef void (*commandFunction_t)( const CArgs& args );

	typedef struct {
		int					flags;
		string_t			description;
		commandFunction_t	func;
		int					size;
	}command_t;

	class ICmdSystem: public ISubSystem  {
	public:
		virtual ~ICmdSystem(){};

		virtual void AddCommand( const string_t& name,  commandFunction_t func, int flags, const string_t& description ) = 0;
		//! remove command by name
		virtual void RemoveCommand( const string_t& name ) = 0;
		//! remove all commands with sett ed flags
		virtual void RemoveCommandByFlag( int flags ) = 0;
		//! execute command
		virtual bool ExecuteCommand( const string_t& commandText ) = 0;
		//! print commands to the console
		virtual void Print( int flags = cmdFlags_All ) = 0;
	};

}
#endif
