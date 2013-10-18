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

#pragma hdrstop
#include "kernel/precompiled.h"
#include "kernel.h"
#include "log.h"
#include "logwritertext.h"
#include "system.h"
#include "varsystem.h"
#include "cmdsystem.h"
#include "filesystem.h"
#include "updatesystem.h"
#include "enginevars.h"

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
		m_initialized	= false;
		m_fileSystem	= NULL;
		m_logWriter		= NULL;
		m_log			= NULL;
		m_varSystem		= NULL;
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
#ifdef  USE_SDL
//		m_renderDriver	= new CRenderDriverSDL(m_varSystem, m_fileSystem);
#endif
		m_updateSystem	= new CUpdateSystem;
//		m_inputSystem	= new CInputSystem(m_renderDriver);

		varSystem		= m_varSystem;

		this->RegisterSubSystem(m_system);
		this->RegisterSubSystem(m_fileSystem);
		this->RegisterSubSystem(m_varSystem);
		this->RegisterSubSystem(m_cmdSystem);
//		this->RegisterSubSystem(m_renderDriver);
		this->RegisterSubSystem((ISubSystem*)m_updateSystem);
//		this->RegisterSubSystem((ISubSystem*)m_inputSystem);

		if (!InitSubSystems() ){
			return false;
		}

//		m_updateSystem->AddUpdaterVariable(m_inputSystem);

		Log("Registered %d subsystems.\n", m_subSystems.size());

		m_initialized = true;

		return m_initialized;
	}

	void CKernel::Shutdown(void) {

		Log("Shutdowns Engine...\n");

		ReleaseSubSystems();

		SafeDelete(m_logWriter);
		SafeDelete(m_log);

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

		Log("  Registering subsystem: '%s'...\n", subSystem->GetName().c_str());
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
		Log("  Initializing all subsystem...\n");
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
		Log("  Release all subsystem...\n");

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
		Log("  Shutdowns all subsystem...\n");

		for( subSystemsVec_t::iterator it = m_subSystems.begin(); it != m_subSystems.end(); ++it ) {
			ISubSystem* subSys = (*it);
			if (subSys == this) {
				continue;
			}

			if (subSys)
				subSys->Shutdown();
		}
	}

	bool CKernel::LoadConfig( string_t fileName ) {
		return true;
	}

	ILog* CKernel::GetLog( void ) {
		return m_log;
	}

	void CKernel::Run() {
		/*
		while (!m_quit) {
			m_updateSystem->Update(0);

			m_updateSystem->Draw();
			// TODO: scene render
			m_renderDriver->SwapBuffers();
		}
		*/
	}

	void CKernel::Quit(){
		m_quit = true;
	}


}

