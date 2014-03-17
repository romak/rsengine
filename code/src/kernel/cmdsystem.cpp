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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "cmdsystem.h"

namespace rengine3d {

	CCmdSystem::CCmdSystem() {
		m_initialized = false;
	}

	CCmdSystem::~CCmdSystem() {
		this->Shutdown();
	}

	string_t CCmdSystem::GetName(void) {
		return "CCmdSystem";
	}

	string_t CCmdSystem::GetDescription(void){
		return "Cmd system";
	}

	string_t CCmdSystem::GetVersion(void){
		return "0.0.1";
	}

	bool CCmdSystem::Init(void) {

		Log("\tInitializing CmdSystem...\n");
		this->AddCommand( "listvars", listVars_f, cmdFlags_Kernel, "List engine registered variables");

		m_initialized = true;;

		return m_initialized;
	}

	void CCmdSystem::Shutdown(void) {
		Log("\tShutdown CmdSystem...\n");

		for ( commandMap_t::iterator it = m_commands.begin(); it != m_commands.end(); ++it ) {
			if ( it->second ) {
				SafeDelete(it->second);
			}
		}
		m_commands.clear();

		m_initialized = false;

	}

	void CCmdSystem::AddCommand( const string_t& name,  commandFunction_t func, int flags, const string_t& description ) {
		command_t* cmd;
		commandMap_t::iterator it = m_commands.find( name ) ;
		if ( it == m_commands.end() ) {
			cmd = new command_t;
			cmd->func			= func;
			cmd->flags			= flags;
			cmd->description	= description;
			cmd->size			= sizeof( command_t ) + (int)cmd->description.size();
			m_commands.insert( commandMap_t::value_type( name, cmd ));
		}
	}

	void CCmdSystem::RemoveCommand( const string_t& name ) {
		commandMap_t::iterator it = m_commands.find( name ) ;

		if ( it != m_commands.end() ) {
			SafeDelete(it->second);
			m_commands.erase( it );
		}
	}

	void CCmdSystem::RemoveCommandByFlag( int flags ) {
	}

	bool CCmdSystem::ExecuteCommand( const string_t& commandText ) {
		command_t*	cmd = NULL;
		char		seps[]   = " \t\n";
		char		*token;
		int			count;
		char		inputArgs[256] = "\0";
		char		commandName[256] = "\0";

		strcpy( m_str, commandText.c_str() );

		count = 0;
		token = strtok( m_str, seps );
		strcpy( commandName, token );
		while( token != NULL ) {
			if ( count > 0) {
				strcat( inputArgs, token );
				strcat( inputArgs, " " );
			}
			count++;
			token = strtok( NULL, seps );
		}

		CArgs args( inputArgs );

		commandMap_t::iterator it = m_commands.find( commandName ) ;

		if ( it != m_commands.end() ) {
			cmd = it->second;
			if ( !cmd ) {
				return false;
			}
			cmd->func( args );
			return true;
		} 

		return false;
	}

	void CCmdSystem::Print( int flags ) {
		command_t* cmd;

		for ( commandMap_t::iterator it = m_commands.begin(); it != m_commands.end(); ++it ) {
			cmd = it->second;
			if ( cmd ) {
				if ( cmd->flags & flags )
					Log("  %s - (%s)\n", it->first.c_str(), cmd->description.c_str());
			}
		}
	}

	void CCmdSystem::listVars_f( const CArgs& args  ) {
		// TODO: получить из агрументов значение флага выводимых переменных
		IKernel* kernel = GetKernel();
		if (kernel) {
			ICmdSystem* cmdSys = kernel->GetCmdSystem();
			cmdSys->Print();
		}
	}

}
