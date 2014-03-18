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

#ifndef __IKERNEL_H__
#define __IKERNEL_H__

namespace rengine3d {

	//!  Interface for engine kernel class
	class IKernel: public ISubSystem {
	public:
		virtual ~IKernel(){};

		virtual bool RegisterSubSystem(ISubSystem* subSystem) = 0;
		virtual ISubSystem* GetSubSystem(string_t name) = 0;

		virtual bool LoadConfig( string_t fileName ) = 0;
		virtual bool SaveConfig( string_t fileName ) = 0;

		virtual ILog* GetLog( void ) = 0;
		virtual IFileSystem* GetFileSystem( void ) = 0;
		virtual IVarSystem* GetVarSystem(void) = 0;
		virtual ICmdSystem* GetCmdSystem( void ) = 0;
		virtual IConsole* GetConsole(void) = 0;
		virtual ISystem* GetSystem(void) = 0;
		virtual IUpdateSystem* GetUpdateSystem(void) = 0;
		virtual IInputSystem* GetInputSystem(void) = 0;
		virtual IRenderDriver* GetRenderDriver() = 0;

		virtual void SetLogFileName(string_t fileName) = 0;

		virtual void Run() = 0;
		virtual void Quit() = 0;
	};


	extern IKernel* GetKernel(void* hwnd = NULL);
	extern void ReleaseKernel();
}

#endif
