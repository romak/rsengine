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
	IResourceManager*	m_resourceManager;
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
	m_resourceManager	= kernel->GetResourceManager();

	IResource* res = m_resourceManager->Add("textures/lensflare0.png", resourceType_t::Texture);
	IResource* tempRes = m_resourceManager->Find("Textures/lensflare0.png", resourceType_t::Texture);

	m_resourceManager->Load();

	m_resourceManager->List(resourceType_t::All);
	camera = scene->CreateCamera3D("camera01");

	updateSys->AddUpdater(this);
	updateSys->AddUpdater(scene);

	inputSys->AddAction(new CActionKeyboard("Escape", inputSys, key_ESCAPE));

	renderDriver->SetWindowCaption("#test application#");
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

