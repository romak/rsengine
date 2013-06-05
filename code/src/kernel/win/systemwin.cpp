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
#include "systemwin.h"

namespace rengine3d {

	static LARGE_INTEGER  m_performanceFrequency;

	typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);

	//String to WCHAR
	std::wstring s2ws(const std::string& s)	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}

	//WCHAR to String
	std::string ws2s(const std::wstring& s){
		int len;
		int slength = (int)s.length() + 1;
		len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
		char* buf = new char[len];
		WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
		std::string r(buf);
		delete[] buf;
		return r;
	}


	CSystemWin::CSystemWin() {
		// Force the main thread to always run on CPU 0.
		// This is done because on some systems QueryPerformanceCounter returns a bit different counter values
		// on the different CPUs (contrary to what it's supposed to do), which can cause negative frame times
		// if the thread is scheduled on the other CPU in the next frame. This can cause very jerky behavior and
		// appear as if frames return out of order.
		SetThreadAffinityMask(GetCurrentThread(), 1);

		// Initialize performance timer
		QueryPerformanceFrequency(&m_performanceFrequency);

		// Initialize the random generator
		srand(static_cast<unsigned int>(GetMicroseconds()));

		m_initialized = false;
	}

	CSystemWin::~CSystemWin(){
		this->Shutdown();
	}

	bool CSystemWin::Init(void){
		m_initialized = true;
		Log("  Initializing windows system...\n");
		return m_initialized;
	}

	void CSystemWin::Shutdown(void){
		Log("  Shutdown windows system...\n");

		m_initialized = false;
	}

	string_t CSystemWin::GetName(void){
		return "CSystemWin";
	}

	string_t CSystemWin::GetDescription(void){
		return "System windows";
	}

	string_t CSystemWin::GetVersion(void){
		return "System windows class";
	}

	string_t CSystemWin::GetOS() const{
		return "TODO";
	}

	string_t CSystemWin::GetPlatform() const{
		return "";
	}

	string_t CSystemWin::GetComputerName() const{
		return "";
	}

	string_t CSystemWin::GetUserName() const{
		return "";
	}

	string_t CSystemWin::GetUserHomeDir() const{
		return "";
	}

	string_t CSystemWin::GetUserDataDir() const {
		// Get application data path
		wchar_t szPath[MAX_PATH];
		SHGetSpecialFolderPathW(nullptr, szPath, CSIDL_APPDATA, FALSE);
		// Return path (copy string)
		return ws2s(szPath);
	}

	string_t CSystemWin::GetExecutableFilename() const{
		// Allocate a buffer that is large enough to hold the information
		wchar_t pszBuffer[256] = L"\0";

		// Get user name as Unicode
		if (GetModuleFileNameW(nullptr, pszBuffer, MAX_PATH)) {
			return ws2s(pszBuffer);
		} else {
			return "";
		}
		return "";
	}

	string_t CSystemWin::GetCurrentDir() const{
		return "";
	}

	bool CSystemWin::SetCurrentDir(const string_t& path){
		return true;
	}

	void CSystemWin::Exit(int ret){

	}

	uint64 CSystemWin::GetMilliseconds() const{
		// Get past time
		LARGE_INTEGER nCurTime;
		QueryPerformanceCounter(&nCurTime);
		LONGLONG nNewTicks = nCurTime.QuadPart;

		// Scale by 1000 in order to get millisecond precision
		nNewTicks *= 1000;
		if (m_performanceFrequency.QuadPart)
			nNewTicks /= m_performanceFrequency.QuadPart;

		// Return past time
		return static_cast<uint64>(nNewTicks);
	}

	uint64 CSystemWin::GetMicroseconds() const{
		// Get past time
		LARGE_INTEGER nCurTime;
		QueryPerformanceCounter(&nCurTime);
		double dNewTicks = static_cast<double>(nCurTime.QuadPart);

		// Scale by 1000000 in order to get microsecond precision
		dNewTicks *= static_cast<double>(1000000.0)/static_cast<double>(m_performanceFrequency.QuadPart);

		// Return past time
		return static_cast<uint64>(dNewTicks);
	}

	void CSystemWin::Sleep(uint64 milliseconds) const{
		SleepEx(static_cast<DWORD>(milliseconds), false);
	}

	char CSystemWin::GetSeparator() const {
		return '\\';
	}


}

