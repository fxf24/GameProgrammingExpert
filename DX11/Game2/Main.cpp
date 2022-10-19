#include "stdafx.h"
#include "Main.h"
Main::Main()
{
}
Main::~Main()
{
}

void Main::Init()
{

	sky = Sky::Create();


	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	Player = Actor::Create();
	Player->LoadFile("Character2.xml");

	Map = Actor::Create();
	Map->LoadFile("Map.xml");

	Point = Light::Create("L1");
	Point2 = Light::Create("L2");

	hammer = Actor::Create();


	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();

}


void Main::Release()
{

}

void Main::Update()
{

	Camera::ControlMainCam();
	LIGHT->RenderDetail();
	//
	////Ui->RenderHierarchy();
	//
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	Point->RenderHierarchy();
	Point2->RenderHierarchy();
	sky->RenderHierarchy();
	Player->RenderHierarchy();
	Cam->RenderHierarchy();
	hammer->RenderHierarchy();
	ImGui::End();


	Cam->Update();
	Grid->Update();
	Player->Update();
	Map->Update();
	Point->Update();
	Point2->Update();
	sky->Update();
	hammer->Update();

}

void Main::LateUpdate()
{
	
}
void Main::Render()
{
	LIGHT->Set();
	Cam->Set();
	sky->Render();
	Point->Render();
	Point2->Render();

	Grid->Render();
	Map->Render();
	hammer->Render();

	BLEND->Set(true);
	Player->Render();
	BLEND->Set(false);

	
}

void Main::ResizeScreen()
{
	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game2");
	App.SetInstance(instance);
	WIN->Create();
	D3D->Create();
	Main* main = new Main();
	main->Init();
	int wParam = (int)WIN->Run(main);
	main->Release();
	SafeDelete(main);
	D3D->DeleteSingleton();
	WIN->DeleteSingleton();
	return wParam;
}
