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
    //Cam = Camera::Create();
    //Cam->LoadFile("Cam.xml");
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
    Sun = Actor::Create();
    Sun->LoadFile("Sun.xml");

    cubeMan = new CubeMan();
    Cam = (Camera*)cubeMan->Find("Camera");
    Camera::main = Cam;
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
    //Cam->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Grid->Update();
    Sun->Update();
    cubeMan->Update();
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
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
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