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

#include "kernel.h"
#include "xml.h"
#include "log.h"
#include "logwritertext.h"
#include "system.h"
#include "varsystem.h"
#include "cmdsystem.h"
#include "filesystem.h"
#include "console.h"
#include "updatesystem.h"
#include "enginevars.h"

#ifdef  USE_SDL
#include "sdl/SDL_config.h"
#include "sdl/SDL.h"
#include "../render/sdl/renderdriver_sdl.h"
#include "../input/sdl/inputsystem_sdl.h"
#endif

namespace rengine3d {

	IKernel*	CKernel::m_kernel	= NULL;
	IVarSystem*	varSystem			= NULL;

	IKernel* GetKernel(void* hwnd) {
		if (!CKernel::m_kernel)
			CKernel::m_kernel = new CKernel();
		return CKernel::m_kernel;
	}

	void ReleaseKernel() {
		if (CKernel::m_kernel) {
			delete CKernel::m_kernel;
			CKernel::m_kernel = NULL;
		}
	}

	// Helper function for log events
	void Log(const char *format, ...) {
		char	text[4096];
		va_list	ap;	

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);

		if (CKernel::m_kernel) {
			ILog* log = CKernel::m_kernel->GetLog();
			if (log) {
				log->Print(text);
			}
		}
	}

	void Warning(const char *format, ...) {
		char	text[4096];
		va_list	ap;	

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);

		if (CKernel::m_kernel) {
			ILog* log = CKernel::m_kernel->GetLog();
			if (log) {
				log->Warning(text);
			}
		}
	}

	void Error(const char *format, ...) {
		char	text[4096];
		va_list	ap;	

		va_start(ap, format);
		vsprintf_s(text, format, ap);
		va_end(ap);

		if (CKernel::m_kernel) {
			ILog* log = CKernel::m_kernel->GetLog();
			if (log) {
				log->Error(text);
			}
		}
	}

	// !!! class declaration begin

	CKernel::CKernel() {

#if defined(PLATFORM_WIN32) && defined(_DEBUG)
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

		m_initialized	= false;

		m_fileSystem	= NULL;
		m_logWriter		= NULL;
		m_log			= NULL;
		m_varSystem		= NULL;
		m_system		= NULL;
		m_updateSystem	= NULL;
		m_renderDriver	= NULL;
		m_inputSystem	= NULL;
		m_console		= NULL;

		m_quit			= false;
		m_logFileName	= logFileName.GetString();
	}

	CKernel::~CKernel() {
	}

	bool CKernel::Init(void) {
		if (m_initialized) 
			return true;

		m_logWriter = new CLogWriterText(m_logFileName);
		m_log		= new CLog(m_logFileName, m_logWriter);

		Log("Initializing Engine...\n");
		Log("Build information: %s\n", BUILD_STRING);

		m_system		= new CSystem();
		m_fileSystem	= new CFileSystem();
		m_varSystem		= new CVarSystem;
		m_cmdSystem		= new CCmdSystem;
		m_updateSystem	= new CUpdateSystem;
		m_console		= new CConsole(this);
#ifdef  USE_SDL
		m_renderDriver	= new CRenderDriverSDL(this);
		m_inputSystem	= new CInputSystemSDL(m_renderDriver);
#endif
		varSystem		= m_varSystem;

		this->RegisterSubSystem(m_system);

		this->RegisterSubSystem(m_fileSystem);
		this->RegisterSubSystem(m_varSystem);
		this->RegisterSubSystem(m_cmdSystem);
		this->RegisterSubSystem(m_console);
		this->RegisterSubSystem(m_renderDriver);
		this->RegisterSubSystem((ISubSystem*)m_updateSystem);
		this->RegisterSubSystem((ISubSystem*)m_inputSystem);

		this->LoadConfig("../../../../data/config/default.cfg");

		if (!InitSubSystems() ){
			return false;
		}

		m_updateSystem->AddUpdaterVariable(m_console);


		Log("Registered %d subsystems.\n", m_subSystems.size());

		m_updateSystem->Print();

		m_initialized = true;

		return m_initialized;
	}

	void CKernel::Shutdown(void) {

		Log("Shutdown Engine...\n");

		this->SaveConfig("default.cfg");

		ReleaseSubSystems();

		SafeDelete(m_logWriter);
		SafeDelete(m_log);

#ifdef  USE_SDL
		SDL_Quit();
#endif

		m_initialized = false;

		ReleaseKernel();
	}

	string_t CKernel::GetName(void) {
		return "CKernel";
	}

	string_t CKernel::GetDescription(void) {
		return "Base kernel implementation";
	}

	string_t CKernel::GetVersion(void) {
		return "0.0.1";
	}

	IRenderDriver* CKernel::GetRenderDriver(void)	{ 
		return m_renderDriver;	
	};

	bool CKernel::RegisterSubSystem(ISubSystem* subSystem) {
		if (!subSystem)
			return false;

		for( subSystemsVec_t::iterator it = m_subSystems.begin(); it != m_subSystems.end(); ++it ) {
			ISubSystem* subSys = (*it);
			if (subSystem == subSys) {
				return true;
			}
		}

		Log("Registering subsystem: '%s'...\n", subSystem->GetName().c_str());
		m_subSystems.push_back(subSystem);

		return true;
	}

	ISubSystem* CKernel::GetSubSystem(string_t name) {

		for( subSystemsVec_t::iterator it = m_subSystems.begin(); it != m_subSystems.end(); ++it ) {
			ISubSystem* subSys = (*it);
			string_t subSysName = subSys->GetName();
			std::transform(subSysName.begin(), subSysName.end(), subSysName.begin(), ::tolower);
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			if ( subSysName == name ) {
				return subSys;
			}
		}

		return NULL;
	}

	bool CKernel::InitSubSystems() {
		Log("\tInitializing all subsystem...\n");
		int numErrors = 0;

		for( subSystemsVec_t::iterator it = m_subSystems.begin(); it != m_subSystems.end(); ++it ) {
			ISubSystem* subSys = (*it);
			if (subSys == this) {
				continue;
			}

			if (!subSys->Init() ) {
				numErrors++;
			}
		}
		return (numErrors == 0);
	}

	void CKernel::ReleaseSubSystems() {
		Log("Release all subsystem...\n");

		for( subSystemsVec_t::iterator it = m_subSystems.begin(); it != m_subSystems.end(); ++it ) {
			ISubSystem* subSys = (*it);
			if (subSys == this) {
				continue;
			}

			subSys->Release();
			subSys = NULL;
		}

		m_subSystems.clear();
	}

	void CKernel::ShutdownSubSystems() {
		Log("Shutdowns all subsystem...\n");

		for( subSystemsVec_t::iterator it = m_subSystems.begin(); it != m_subSystems.end(); ++it ) {
			ISubSystem* subSys = (*it);
			if (subSys == this) {
				continue;
			}

			if (subSys) {
				subSys->Shutdown();
			}
		}
	}

	bool CKernel::LoadConfig( string_t fileName ) {
		IXML* xml = m_fileSystem->CreateXML();
		if (!xml->Load(fileName.c_str())) {
			SafeDelete(xml);
			return false;
		}

		m_varSystem->LoadVariables(xml);

		SafeDelete(xml);

		return true;
	}

	bool CKernel::SaveConfig( string_t fileName ) {
		IXML* xml = m_fileSystem->CreateXML();
		if (!xml->Load(fileName.c_str())) {
			SafeDelete(xml);
			return false;
		}

		m_varSystem->SaveVariables(CVAR_ARCHIVE, xml);

		SafeDelete(xml);

		return true;
	}

	ILog* CKernel::GetLog( void ) {
		return m_log;
	}

#ifdef  USE_SDL
	void CKernel::SDL_OnEvent(void* _Event) {
		SDL_Event* Event = (SDL_Event*)_Event;

		switch(Event->type) {

		case SDL_KEYDOWN: {
			//Log("Key down\n");
			m_inputSystem->ProcessEvent(Event);

			break; }
		case SDL_KEYUP: {
			//Log("Key up\n");
			m_inputSystem->ProcessEvent(Event);
			break; }
		case SDL_MOUSEMOTION: {
			m_inputSystem->ProcessEvent(Event);
			break; }

		case SDL_MOUSEBUTTONDOWN: {
			switch(Event->button.button) {
			case SDL_BUTTON_LEFT: {
				//Log("Left mouse button down\n");
				break; }
			case SDL_BUTTON_RIGHT: {
				//Log("Right mouse button down\n");
				break; }
			case SDL_BUTTON_MIDDLE: {
				//Log("Middle mouse button down\n");
				break; }
			}
			m_inputSystem->ProcessEvent(Event);

			break; }

		case SDL_MOUSEBUTTONUP:	{
			switch(Event->button.button) {
			case SDL_BUTTON_LEFT: {
				break; }
			case SDL_BUTTON_RIGHT: {
				break; }
			case SDL_BUTTON_MIDDLE: {
				break; }
			}
			m_inputSystem->ProcessEvent(Event);

			break; }

		case SDL_QUIT: {
			m_quit = true;
			break; }

		case SDL_SYSWMEVENT: {
			break; }

		case SDL_WINDOWEVENT: {
			switch(Event->window.event) {
			case SDL_WINDOWEVENT_SHOWN: {
				//Log("Window %d shown\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_HIDDEN: {
				//Log("Window %d hidden\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_EXPOSED: {
				//Log("Window %d exposed\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_MOVED: {
				//Log("Window %d moved to %d,%d\n", Event->window.windowID, Event->window.data1,Event->window.data2);
				break; }
			case SDL_WINDOWEVENT_RESIZED: {
				//Log("Window %d resized to %dx%d\n", Event->window.windowID, Event->window.data1, Event->window.data2);
				break; }
			case SDL_WINDOWEVENT_MINIMIZED: {
				//Log("Window %d minimized\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_MAXIMIZED: {
				//Log("Window %d maximized\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_RESTORED: {
				//Log("Window %d restored\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_ENTER: {
				//Log("Mouse entered window %d\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_LEAVE: {
				//Log("Mouse left window %d\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_FOCUS_GAINED: {
				//Log("Window %d gained keyboard focus\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_FOCUS_LOST: {
				//Log("Window %d lost keyboard focus\n", Event->window.windowID);
				break; }
			case SDL_WINDOWEVENT_CLOSE: {
				//Log("Window %d closed\n", Event->window.windowID);
				break; }
			}
			break; }
		default: {
			break;}
		}
	}

#endif

	void CKernel::Run() {
#ifdef  USE_SDL
		SDL_Event Event;

		while(!m_quit) {

			while(SDL_PollEvent(&Event)) {
				SDL_OnEvent(&Event);
			}

			m_inputSystem->Update(0);

			m_updateSystem->OnUpdate(0);

			m_inputSystem->EndUpdate();

			// TODO: scene render

			m_renderDriver->ClearScreen();

			m_updateSystem->OnDraw();

			m_renderDriver->SwapBuffers();
		}
#endif
	}

	void CKernel::Quit(){
		m_quit = true;
	}


}

