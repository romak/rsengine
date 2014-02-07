#include "stdafx.h"

#include "kernel/precompiled.h"

using namespace rengine3d;

class CMainApp: public IUpdateable {
public:
	CMainApp();
	~CMainApp();

	virtual void OnUpdate(real timeStep);
	virtual void OnDraw();

	void Run();

private:
	IKernel*		kernel;
	IVarSystem*		varSys;
	ISystem*		m_sys;
};

CMainApp::CMainApp(): IUpdateable("CMainApp") {	
	kernel = GetKernel();

	if (!kernel->Init() ) {
		kernel->Shutdown();
		return;
	}

	varSys	= kernel->GetVarSystem();
	m_sys	= kernel->GetSystem();

	m_sys->SetWindowCaption("test application");

}

CMainApp::~CMainApp() {
	kernel->Shutdown();
}

void CMainApp::OnUpdate(real timeStep) {
	//if (inputSys->CheckAction("Escape")) {
	//	kernel->Quit();
	//}
}

void CMainApp::OnDraw() {
}

void CMainApp::Run() {
	kernel->Run();
}

int _tmain(int argc, _TCHAR* argv[]) {
	CMainApp* app = new CMainApp;
	app->Run();
	SafeDelete(app);
	return 0;
}

