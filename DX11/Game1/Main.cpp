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
    /*Cam = new Camera();
    Cam->name = "Cam";
    Camera::main = Cam;*/
    
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
   /* Sun = Actor::Create();
    Sun->LoadFile("Sun.xml");*/

    cubeMan = new CubeMan();
    //Cam = (Camera*)cubeMan->Find("Cam");
    //cubeMan->AddChild(Cam);
    //Cam->SaveFile()
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    //Sun->Release();
    Grid->Release();
    cubeMan->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d",TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    //Sun->RenderHierarchy();
    Grid->RenderHierarchy();
    cubeMan->RenderHierarchy();
    ImGui::End();


    Camera::main->Update();
    Grid->Update();
    //Sun->Update();
    cubeMan->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    Camera::main->Set();
    Grid->Render();
    //Sun->Render();
    cubeMan->Render();
}

void Main::ResizeScreen()
{
    Camera::main->w = App.GetWidth();
    Camera::main->h = App.GetHeight();
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