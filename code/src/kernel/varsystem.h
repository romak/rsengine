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

#ifndef __VAR_SYSTEM_H__
#define __VAR_SYSTEM_H__

namespace rengine3d {

	class CVar: public IVar {
	public:
		CVar( string_t name, string_t value, int flags, string_t description );
		virtual ~CVar();

		virtual string_t GetName( void );
		virtual int GetFlags( void );
		virtual string_t GetDesc( void );
		virtual string_t GetString( void );
		virtual int GetInt( void );
		virtual bool GetBool( void );
		virtual real GetFloat( void );
		virtual CVec3 GetVec3( void );

		virtual void SetString( string_t value );
		virtual void SetInt( int value );
		virtual void SetBool( bool value );
		virtual void SetFloat( real value );
		virtual void SetVec3( const CVec3& value );
		virtual void SetFlags( const int flags );

		virtual bool IsModified( void ) const;
		virtual void SetModified( void );
		virtual void ClearModified( void );

		static void RegisterStaticVars( void );
	private:
		void Init( string_t name, string_t value, int flags, string_t description );
	private:
		string_t		m_name;
		string_t		m_description;
		string_t		m_value;
		CVec3			m_vec3;
		int				m_intValue;
		real			m_floatValue;
		int				m_flags;
		CVar*			m_next;
		static CVar*	m_staticVars;
	};

	class CVarSystem: public IVarSystem {
	public:
		CVarSystem();
		virtual ~CVarSystem();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual bool IsInitialized(void) { return m_initialized; };

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		virtual void Register( IVar* var );
		virtual IVar* CreateVar( string_t name, string_t value, int flags, string_t description );
		virtual IVar* Find( string_t name );

		virtual void SetString( string_t name, string_t value, int flags = 0 );
		virtual void SetInt( string_t name, int value, int flags = 0 );
		virtual void SetBool( string_t name, bool value, int flags = 0 );
		virtual void SetFloat( string_t name, real value, int flags = 0 );
		virtual void SetVec3( string_t name, const CVec3& value, int flags = 0 );

		virtual string_t GetString( string_t name );
		virtual int GetInt( string_t name );
		virtual bool GetBool( string_t name );
		virtual real GetFloat( string_t name );
		virtual CVec3 GetVec3( string_t name );

		virtual void Print( int flags = CVAR_ALL );

		virtual string_t GetClassName() { return "CVarSystem"; };
	private:
		typedef std::map< string_t, IVar* > varList_t;
		static varList_t	m_variables;
	};

}
#endif
