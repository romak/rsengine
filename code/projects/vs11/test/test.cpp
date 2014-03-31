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
	IMouseDevice*		mouseDevice;
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
	mouseDevice		= inputSys->GetMouseDevice();

	updateSys->AddUpdater(this);

	inputSys->AddAction(new CActionKeyboard("Escape", inputSys, key_ESCAPE));

	renderDriver->SetWindowCaption("#test application#");

	CVec3 axis = CVec3(1,0,0);
	real angle = 10;
	CQuat q1;
	q1.SetFromAxisAngle(axis, angle);

	CMat4 m;
	m.Scale(1,0,0);


}

CMainApp::~CMainApp() {
	kernel->Shutdown();
}

void CMainApp::OnUpdate(real timeStep) {
	uint keyMod = keyboardDevice->GetModifiers();

	if (inputSys->CheckAction("Escape")) {
		kernel->Quit();
	}

	if ((keyboardDevice->KeyIsDown(key_RETURN)) && (keyMod & keyModifier_Alt)) {
		bool fs = !renderDriver->GetFullScreen();
		renderDriver->SetFullScreen(fs);
		Log("Alt Key enter -)\n");
	}

	if (keyboardDevice->KeyIsDown(key_UP)) {
		Log("Key up -)\n");
	}
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

