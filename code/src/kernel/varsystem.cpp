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
#include "varsystem.h"

namespace rengine3d {

	CVar*					CVar::m_staticVars = NULL;
	CVarSystem::varList_t	CVarSystem::m_variables;
	extern					IVarSystem* varSystem;

	char* va( const char *fmt, ... );

	CVar::CVar( string_t name, string_t value, int flags, string_t description ) {
		Init( name, value, flags, description );
	}

	CVar::~CVar() {
	}

	string_t CVar::GetName( void ) {
		return m_name; 
	}

	int CVar::GetFlags( void ) {
		return m_flags;
	}

	string_t CVar::GetDesc( void ) {
		return m_description;
	}

	string_t CVar::GetString( void ) {
		return m_value; 
	}

	int CVar::GetInt( void ) {
		return m_intValue; 
	}

	bool CVar::GetBool( void ) {
		return ( m_intValue != 0 ); 
	}

	real CVar::GetFloat( void ) {
		return m_floatValue; 
	}

	CVec3 CVar::GetVec3( void ) {
		return m_vec3; 
	}

	void CVar::SetString( string_t value ) {
		m_value			= value;
		m_intValue		= atoi( value.c_str() );
		m_floatValue	= (real)atof( value.c_str() );
	}

	void CVar::SetInt( int value ) {
		m_value			= va( "%i", value );
		m_intValue		= value;
		m_floatValue	= (real) value;
	}

	void CVar::SetBool( bool value ) {
		m_value			= va( "%i", value );
		m_intValue		= (bool) value;
		m_floatValue	= (real) value;
	}

	void CVar::SetFloat( real value ) {
		m_value			= va( "%f", value );
		m_intValue		= (int) value;
		m_floatValue	= value;
	}

	void CVar::SetVec3( const CVec3& value ) {
		m_value			= va( "%f %f %f", value.x, value.y, value.z );
		m_intValue		= 0;
		m_floatValue	= 0;
		m_vec3			= value;
	}

	void CVar::SetFlags( const int flags ) {
		m_flags |= flags; 
	}

	bool CVar::IsModified( void ) const {
		return ( m_flags & CVAR_MODIFIED ) != 0; 
	}

	void CVar::SetModified( void ) {
		m_flags |= CVAR_MODIFIED; 
	}

	void CVar::ClearModified( void ) {
		m_flags &= ~CVAR_MODIFIED;
	}

	void CVar::Init( string_t name, string_t value, int flags, string_t description ) {
		m_name			= name;
		m_description	= description;
		m_value			= value;

		m_intValue		= atoi(value.c_str());
		m_floatValue	= (real)atof(value.c_str());

		m_flags			= flags;

		if ( flags & CVAR_VEC3 ) {
			sscanf_s( value.c_str(), "%f %f %f", &m_vec3.x, &m_vec3.y, &m_vec3.z );
		}

		if ( varSystem ) {
			varSystem->Register( this );
		} else 
		{
			m_flags			= flags | CVAR_STATIC;
			this->m_next	= m_staticVars;
			m_staticVars	= this;
		}

	}

	void CVar::RegisterStaticVars( void ) {
		int numVars = 0;
		for ( CVar *var = m_staticVars; var; var = var->m_next ) {
			if ( varSystem ) {
				varSystem->Register( var );
				numVars++;
			}
		}

		Log("\t\tRegistered %d static vars.\n", numVars);

	}

	// --- CVarSystem --- 

	CVarSystem::CVarSystem() {
		m_initialized = false;
	}

	CVarSystem::~CVarSystem() {
		this->Shutdown();
	}

	string_t CVarSystem::GetName(void) {
		return "CVarSystem";
	}

	string_t CVarSystem::GetDescription(void) {
		return "Var system";
	}

	string_t CVarSystem::GetVersion(void){
		return "0.0.1";
	}

	bool CVarSystem::Init(void) {
		Log("\tInitializing VarSystem...\n");
		CVar::RegisterStaticVars();

		m_initialized = true;

		return m_initialized;
	}

	void CVarSystem::Shutdown(void) {
		Log("\tShutdown VarSystem...\n");

		for ( varList_t::iterator it = m_variables.begin(); it != m_variables.end(); ++it ) {
			if (!( it->second->GetFlags() & CVAR_STATIC ))
				SafeDelete(it->second);
		}

		m_variables.clear();

		m_initialized = false;

	}

	void CVarSystem::Register( IVar* var ) {
		varList_t::iterator it = m_variables.find( var->GetName() ) ;

		if ( it == m_variables.end() ) {
			m_variables.insert( varList_t::value_type( var->GetName(), var) );
		}
	}

	IVar* CVarSystem::CreateVar( string_t name, string_t value, int flags, string_t description ) {
		IVar* var = this->Find( name );
		if ( var )
			return var;

		var = new CVar( name, value, flags, description );
		return var;
	}

	IVar* CVarSystem::Find( string_t name ) {
		varList_t::iterator it = m_variables.find( name ) ;

		if ( it != m_variables.end() ) {
			return it->second;
		}

		return NULL;
	}

	void CVarSystem::SetString( string_t name, string_t value, int flags ) {
		IVar *var = this->Find( name );

		if ( !var )
			return;

		var->SetString( value );
		var->SetFlags( flags );
		var->SetModified();
	}

	void CVarSystem::SetInt( string_t name, int value, int flags ) {
		IVar *var = this->Find( name );

		if ( !var )
			return;

		var->SetInt( value );
		var->SetFlags( flags );
		var->SetModified();
	}

	void CVarSystem::SetBool( string_t name, bool value, int flags ) {
		IVar *var = Find( name );

		if ( !var )
			return;

		var->SetBool( value );
		var->SetFlags( flags );
		var->SetModified();
	}

	void CVarSystem::SetFloat( string_t name, real value, int flags ) {
		IVar *var = this->Find( name );

		if ( !var )
			return;

		var->SetFloat( value );
		var->SetFlags( flags );
		var->SetModified();
	}

	void CVarSystem::SetVec3( string_t name, const CVec3& value, int flags ) {
		IVar *var = this->Find( name );

		if ( !var )
			return;

		var->SetVec3( value );
		var->SetFlags( flags );
		var->SetModified();
	}

	string_t CVarSystem::GetString( string_t name ) {
		IVar *var = this->Find( name );

		if ( var )
			return var->GetString();

		return "";
	}

	int CVarSystem::GetInt( string_t name ) {
		IVar* var = Find( name );

		if ( var )
			return var->GetInt();

		return 0;
	}

	bool CVarSystem::GetBool( string_t name ) {
		IVar* var = Find( name );

		if ( var )
			return var->GetBool();

		return false;
	}

	real CVarSystem::GetFloat( string_t name ) {
		IVar* var = Find( name );

		if ( var )
			return var->GetFloat();

		return 0.0f;
	}

	CVec3 CVarSystem::GetVec3( string_t name ) {
		IVar* var = Find( name );

		if ( var )
			return var->GetVec3();

		return CVec3( 0.0f, 0.0f, 0.0f );
	}

	void CVarSystem::Print( int flags ) {
		IVar* var;

		for ( varList_t::iterator it = m_variables.begin(); it != m_variables.end(); ++it ) {
			var = it->second;
			if ( var->GetFlags() & flags ) {
				Log( "  %s = %s\n", var->GetName(), var->GetString() );
			}
		}
	}

	// --- Help-in functions ---
	char* va( const char *fmt, ... ) {
		va_list argptr;
		static int index = 0;
		static char string[4][16384];	// in case called by nested functions
		char *buf;

		buf = string[index];
		index = (index + 1) & 3;

		va_start( argptr, fmt );
		vsprintf( buf, fmt, argptr );
		va_end( argptr );

		return buf;
	}

}
