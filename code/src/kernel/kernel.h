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

#ifndef __CKERNEL_H__
#define __CKERNEL_H__

namespace rengine3d {

	class CKernel: public IKernel {
	public:
		CKernel();
		virtual ~CKernel();

		virtual bool Init(void);
		virtual void Shutdown(void);

		virtual bool IsInitialized(void) { return m_initialized; };

		virtual string_t GetName(void);
		virtual string_t GetDescription(void);
		virtual string_t GetVersion(void);

		virtual bool RegisterSubSystem(ISubSystem* subSystem);
		virtual ISubSystem* GetSubSystem(string_t name);

		virtual bool LoadConfig( string_t fileName );

		virtual ILog* GetLog( void );
		virtual IFileSystem* GetFileSystem(void)	{ return m_fileSystem; };
		virtual IVarSystem* GetVarSystem(void)		{ return m_varSystem;  };
		virtual ICmdSystem* GetCmdSystem( void )	{ return m_cmdSystem;  }; 
		virtual ISystem* GetSystem(void)			{ return m_system;	   };
		virtual IUpdateSystem* GetUpdateSystem(void){ return m_updateSystem;};
		//		virtual IInputSystem* GetInputSystem(void)			{ return m_inputSystem;	   };
		virtual IRenderDriver* GetRenderDriver(void);
		virtual void SetLogFileName(string_t fileName)	{ m_logFileName = fileName;	};

		virtual void Run() ;
		virtual void Quit();
	public:
		static IKernel*	m_kernel;
	protected:
		bool InitSubSystems();
		void ShutdownSubSystems();
		void ReleaseSubSystems();
	protected:
		bool				m_quit;
		string_t			m_logFileName;

		typedef std::vector<ISubSystem*> subSystemsVec_t;
		subSystemsVec_t		m_subSystems;

		ILog*				m_log;
		ILogWriter*			m_logWriter;

		IFileSystem*		m_fileSystem;
		IVarSystem*			m_varSystem;
		ICmdSystem*			m_cmdSystem;
		ISystem*			m_system;
		IUpdateSystem*		m_updateSystem;
		IRenderDriver*		m_renderDriver;
		//		CInputSystem*		m_inputSystem;
	};

}

#endif
