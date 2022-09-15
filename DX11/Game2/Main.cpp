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
	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");


	inv.Init();

	ResizeScreen();
}

void Main::Release()
{
	
}


void Main::Update()
{
	Camera::ControlMainCam();
	

	Cam->Update();
	Grid->Update();
	inv.Update();

	ImGui::Text("Mouse  X: %f Y: %f", INPUT->NDCPosition.x,
		INPUT->NDCPosition.y);
}

void Main::LateUpdate()
{

}

void Main::Render()
{
	Cam->Set();
	
	Grid->Render();
	//���� ������ ���� �׸��� ���������� ������
	
	inv.Render();
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
