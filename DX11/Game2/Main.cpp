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

	Map = Terrain::Create();
	//Map->LoadFile("Map.xml");
	Map->LoadFile("Map2.xml");
	Map->CreateStructuredBuffer();

	Point = Light::Create("L1");
	Point2 = Light::Create("L2");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Sphere[i][j] = Actor::Create();
			Sphere[i][j]->LoadFile("Sphere.xml");
			Sphere[i][j]->SetWorldPos(Vector3(-85.0f + i * 85.0f, 0.0f,
				85.0f - j * 85.0f));
		}
	}


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
	Pos.x = (Player->GetWorldPos().x + 128.0f) / (256.0f / 3.0f);
	Pos.y = (Player->GetWorldPos().z - 128.0f) / (-256.0f / 3.0f);

	ImGui::Text("X: %d  Y: %d ", Pos.x, Pos.y);

	


	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	Camera::ControlMainCam();
	LIGHT->RenderDetail();
	//
	////Ui->RenderHierarchy();
	//
	ImGui::Begin("Hierarchy");
	Point->RenderHierarchy();
	Point2->RenderHierarchy();
	sky->RenderHierarchy();
	Player->RenderHierarchy();
	Cam->RenderHierarchy();
	ImGui::End();


	Cam->Update();
	Grid->Update();
	Player->Update();
	Map->Update();
	Point->Update();
	Point2->Update();
	sky->Update();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Sphere[i][j]->Update();

		}
	}
}

void Main::LateUpdate()
{
	Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
	Vector3 Hit;
	//if (Map->ComPutePicking(Mouse, Hit))
	if (Map->ComPutePicking(Mouse, Hit))
	{
		Player->SetWorldPos(Hit);
		cout << endl;
	}


}
void Main::Render()
{
	LIGHT->Set();
	Cam->Set();
	sky->Render();
	Point->Render();
	Point2->Render();

	Grid->Render();


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Sphere[i][j]->Render();

		}
	}

	//BLEND->Set(true);
	Player->Render();
	//BLEND->Set(false);



	Map->Render();
	
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
