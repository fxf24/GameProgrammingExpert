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
    Cam = new Camera();
    Camera::main = Cam;
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
    Sun = Actor::Create();
    Sun->LoadFile("Sun.xml");

    cubeMan = new CubeMan();
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Sun->Release();
    Grid->Release();
    cubeMan->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d",TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Sun->RenderHierarchy();
    Grid->RenderHierarchy();
    cubeMan->RenderHierarchy();

    ImGui::End();


    Cam->Update();
    Grid->Update();
    cubeMan->Update();
    Sun->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    Cam->Set();
    Grid->Render();
    Sun->Render();
    cubeMan->Render();

}

void Main::ResizeScreen()
{
    Cam->w = App.GetWidth();
    Cam->h = App.GetHeight();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game1");
	App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
	Main * main = new Main();
    main->Init();
	int wParam = (int)WIN->Run(main);
    main->Release();
	SafeDelete(main);
    D3D->DeleteSingleton();
	WIN->DeleteSingleton();

	return wParam;
}