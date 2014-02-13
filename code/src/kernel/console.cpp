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
#include "console.h"

namespace rengine3d {

	const string_t CONSOLE_VERSION = "0.0.1";

	CConsole::CConsole(IKernel* kernel): IConsole("CConsole"), m_active(false), m_kernel(kernel) {
	}

	CConsole::~CConsole() {
		this->Shutdown();
	}

	string_t CConsole::GetName(void) {
		return "CConsole";
	}

	string_t CConsole::GetDescription(void) {
		return "Console";
	}

	string_t CConsole::GetVersion(void) {
		return CONSOLE_VERSION;
	}

	bool CConsole::Init(void) {
		if (m_initialized) 
			return true;

		Log("\tInitializing Console...\n");
		m_initialized = true;
		return m_initialized;
	}

	void CConsole::Shutdown(void) {
		Log("\tShutdown Console...\n");
		m_initialized = false;
	}

	void CConsole::Clear() {
	}

	bool CConsole::IsActive() {
		return m_active;
	}

	void CConsole::Print(const char *text) {
	}

	void CConsole::OnInit(void) {
	}

	void CConsole::OnShutdown(void) {
	}

	void CConsole::OnDraw(void) {
		if (!m_active)
			return;

	}

	void CConsole::OnUpdate(real timeStep){
		if (!m_active)
			return;

	}

	void CConsole::OnKeyDown(int sym, int mod, uint unicode) {
		if (!m_active)
			return;
	}

    void CConsole::OnKeyUp(int sym, int mod, uint unicode) {
		if (!m_active)
			return;

	}

}
