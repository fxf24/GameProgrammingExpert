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

	Sp1 = Actor::Create();
	Sp1->LoadFile("Sphere.xml");

	Sp2 = Actor::Create();
	Sp2->LoadFile("Sphere.xml");
	Sp2->scale = Vector3(5, 5, 5);
	lerpValue = 0.0f;
}

void Main::Release()
{
	
}


void Main::Update()
{
	Camera::ControlMainCam();
	for (int i = 0; i < 4; i++)
	{
		string str = "Point" + to_string(i);
		ImGui::SliderFloat3(str.c_str(), (float*)&Point[i], -100.0f, 100.0);
	}
	



	lerpValue += DELTA;

	if (lerpValue > 1.0f)
		lerpValue = 0.0f;


	Sp1->SetWorldPos(Util::Cubic(Point[0], Point[1], Point[2], Point[3], lerpValue));

	Sp1->Update();
	Cam->Update();
	Grid->Update();
}

void Main::LateUpdate()
{
}
void Main::Render()
{
	Cam->Set();
	for (int i = 0; i < 4; i++)
	{
		Sp2->SetWorldPos(Point[i]);
		Sp2->Update();
		Sp2->Render();
	}

	Grid->Render();
	Sp1->Render();
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
