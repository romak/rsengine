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

#ifndef __CMD_SYSTEM_H__
#define __CMD_SYSTEM_H__

namespace rengine3d {

	class ICmdSystem;

	class CCmdSystem: public ICmdSystem {
	public:
		CCmdSystem();
		virtual ~CCmdSystem();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		virtual void AddCommand( const string_t& name,  commandFunction_t func, int flags, const string_t& description );
		virtual void RemoveCommand( const string_t& name );
		virtual void RemoveCommandByFlag( int flags );
		virtual bool ExecuteCommand( const string_t& commandText );
		virtual void Print( int flags = cmdFlags_All );

		virtual string_t GetClassName() { return "CCmdSystem"; };
	private:
		static void listVars_f( const CArgs& args  );
	protected:
		typedef std::map< string_t, command_t* > commandMap_t;
		commandMap_t		m_commands;
		char				m_str[256];
	};

}

#endif
