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

#if PLATFORM == PLATFORM_WIN32
#include "./win/systemwin.h"
#elif defined(PLATFORM_LINUX)
#endif

#include "system.h"

namespace rengine3d {

	CSystem::CSystem(): m_system(NULL) {
		#if PLATFORM == PLATFORM_WIN32
			m_system = new CSystemWin();
		#elif defined(PLATFORM_LINUX)
		#else
		#endif
	}

	CSystem::~CSystem(){
		SafeDelete(m_system);
	}

	bool CSystem::Init(void) {
		return m_system->Init();
	}

	void CSystem::Shutdown(void){
		m_system->Shutdown();
	}

	string_t CSystem::GetName(void) {
		return m_system->GetName();
	}

	string_t CSystem::GetDescription(void) {
		return m_system->GetDescription();
	}

	string_t CSystem::GetVersion(void) {
		return m_system->GetVersion();
	}

	string_t CSystem::GetOS() const{
		return m_system->GetOS();
	}

	string_t CSystem::GetPlatform() const{
		return m_system->GetPlatform();
	}

	string_t CSystem::GetComputerName() const{
		return m_system->GetComputerName();
	}

	string_t CSystem::GetUserName() const{
		return m_system->GetUserName();
	}

	string_t CSystem::GetUserHomeDir() const{
		return m_system->GetUserHomeDir();
	}

	string_t CSystem::GetUserDataDir() const {
		return m_system->GetUserDataDir();
	}

	string_t CSystem::GetExecutableFilename() const{
		return m_system->GetExecutableFilename();
	}

	string_t CSystem::GetCurrentDir() const{
		return m_system->GetCurrentDir();
	}

	bool CSystem::SetCurrentDir(const string_t& path){
		return m_system->SetCurrentDir(path);
	}

	void CSystem::Exit(int ret){
		m_system->Exit(ret);
	}

	uint64 CSystem::GetMilliseconds() const{
		return m_system->GetMilliseconds();
	}

	uint64 CSystem::GetMicroseconds() const{
		return m_system->GetMicroseconds();
	}

	void CSystem::Sleep(uint64 milliseconds) const{
		m_system->Sleep(milliseconds);
	}

	char CSystem::GetSeparator() const {
		return m_system->GetSeparator();
	}

}