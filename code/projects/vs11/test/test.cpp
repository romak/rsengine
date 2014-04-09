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
	ICamera3D*			camera;
	IScene*				scene;
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
	scene			= kernel->GetScene();

	camera = scene->CreateCamera3D("camera01");

	updateSys->AddUpdater(this);
	updateSys->AddUpdater(scene);

	inputSys->AddAction(new CActionKeyboard("Escape", inputSys, key_ESCAPE));

	renderDriver->SetWindowCaption("#test application#");

	CQuat q1;
	CVec3 v1;
	q1.Normalize();

	v1 = q1.Rotate(CVec3(45,0,0));

	real a,b,r;
	a = 10;
	b = 20;
	r = Interpolate(a, b, 2);
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

