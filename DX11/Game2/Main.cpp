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
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	sp1 = Actor::Create();
	sp1->LoadFile("Sphere.xml");
	
	sp2 = Actor::Create();
	sp2->LoadFile("Sphere.xml");
	sp2->scale = Vector3(5, 5, 5);

	Camera::main = Cam;

	lerpValue = 0.0f;
}

void Main::Release()
{
	
}


void Main::Update()
{
	Camera::ControlMainCam();

	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	Cam->RenderHierarchy();
	Grid->RenderHierarchy();
	ImGui::End();

	for (int i = 0; i < 4; i++)
	{
		string str = "Point" + to_string(i);
		ImGui::SliderFloat3(str.c_str(), (float*)&Point[i], -100.0f, 100.0);
	}
	lerpValue += DELTA;

	if (lerpValue > 1.0f)
		lerpValue = 0.0f;

	sp1->SetWorldPos(Util::Cubic(Point[0], Point[1], Point[2], Point[3], lerpValue));

	sp1->Update();

	Cam->Update();
	Grid->Update();
}

void Main::LateUpdate()
{
}
void Main::Render()
{
	Cam->Set();
	Grid->Render();

	for (int i = 0; i < 4; i++)
	{
		sp2->SetWorldPos(Point[i]);
		sp2->Update();
		sp2->Render();
	}

	sp1->Render();
}

void Main::ResizeScreen()
{

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
