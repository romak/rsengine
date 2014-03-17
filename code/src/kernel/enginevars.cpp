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
#include "enginevars.h"

namespace rengine3d {

	CVar version		( "version", BUILD_STRING,	CVAR_KERNEL		| CVAR_STRING | CVAR_READONLY, "engine version" );
	CVar developer		( "developer", "1",			CVAR_KERNEL		| CVAR_INT, "developer mode" );
	CVar r_fullscreen	( "r_fullscreen", "0",		CVAR_RENDERER	| CVAR_BOOL | CVAR_ARCHIVE, "renderer full screen mode" );
	CVar r_width		( "r_width", "800",			CVAR_RENDERER	| CVAR_INT | CVAR_ARCHIVE, "renderer screen width" );
	CVar r_height		( "r_height", "600",		CVAR_RENDERER	| CVAR_INT | CVAR_ARCHIVE, "renderer screen height" ); 
	CVar v_sync			( "v_sync", "0",			CVAR_RENDERER	| CVAR_BOOL | CVAR_ARCHIVE, "renderer v_sync" ); 
	CVar r_clear		( "r_clear", "1",			CVAR_RENDERER	| CVAR_BOOL , "clear background every frame" );
	CVar logFileName	( "logFileName", "rengine3d.log",CVAR_KERNEL| CVAR_STRING | CVAR_ARCHIVE, "engine log file name" ); 
}
