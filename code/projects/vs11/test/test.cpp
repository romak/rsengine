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
	IKernel*			kernel;
	IVarSystem*			varSys;
	ISystem*			sys;
	IRenderDriver*		renderDriver;
	IUpdateSystem*		updateSys;
	IKeyboardDevice*	keyboardDevice;
	IInputSystem*		inputSys;
};

CMainApp::CMainApp(): IUpdateable("CMainApp") {	
	kernel = GetKernel();

	if (!kernel->Init() ) {
		kernel->Shutdown();
		return;
	}

	varSys			= kernel->GetVarSystem();
	sys				= kernel->GetSystem();
	updateSys		= kernel->GetUpdateSystem();
	renderDriver	= kernel->GetRenderDriver();
	inputSys		= kernel->GetInputSystem();
	keyboardDevice	= inputSys->GetKeyboardDevice();

	updateSys->AddUpdater(this);

	inputSys->AddAction(new CActionKeyboard("Escape", inputSys, key_ESCAPE));

	renderDriver->SetWindowCaption("test application");

}

CMainApp::~CMainApp() {
	kernel->Shutdown();
}

void CMainApp::OnUpdate(real timeStep) {
	if (inputSys->CheckAction("Escape")) {
		kernel->Quit();
	}


	if (keyboardDevice->KeyIsDown(key_UP)) {
		Log("Key up -)\n");
	}

	//if (keyboardDevice->KeyIsDown(key_ESCAPE)) {
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

