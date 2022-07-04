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
    App.fixFrame = 1000000;
    Cam = new Camera();
    Camera::main = Cam;

    Grid = Actor::Create();
    Grid->mesh = RESOURCE->LoadMesh("1.Grid.mesh");

    Sun = Actor::Create();
    Sun->position.x = 0.0f;
    Sun->position.y = 0.0f;
    Sun->scale.x = 1.0f;
    Sun->scale.y = 1.0f;

    //Sun.mesh.reset();
    //Sun.mesh = nullptr;
    for (int i = 0; i < 5; i++)
    {
        GameObject* SunBone = GameObject::Create("SunBone" + to_string(i));
        Sun->AddChild(SunBone);
        GameObject* Planet = GameObject::Create("Planet" + to_string(i));
        SunBone->AddChild(Planet);

        Planet->position.x = 2.0f * (i + 1);
        Planet->position.y = 2.0f * (i + 1);

        Planet->scale.x = 1.0f;
        Planet->scale.y = 1.0f;
    }
    //
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Sun->Release();
    Grid->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    

    ImGui::Text("FPS: %d",TIMER->GetFramePerSecond());
    ImGui::Begin("Hierirchy");
    //ImVec2 pos(200, 200);
    //ImGui::SetWindowPos(pos);
    //ImGui::SetWindowSize(pos);
    Sun->RenderImGui();
    ImGui::End();

    /*if (INPUT->KeyPress('1'))
    {
        Cam->fov += 3.14f * DELTA;
    }
    if (INPUT->KeyPress('2'))
    {
        Cam->fov -= 3.14f * DELTA;
    }

    if (INPUT->KeyPress('A'))
    {
        Cam->position += -Cam->GetRight() * 100.0f * DELTA;
    }
    if (INPUT->KeyPress('D'))
    {
        Cam->position += Cam->GetRight() * 100.0f * DELTA;
    }
    if (INPUT->KeyPress('W'))
    {
        Cam->position += Cam->GetForward() * 100.0f * DELTA;
    }
    if (INPUT->KeyPress('S'))
    {
        Cam->position += -Cam->GetForward() * 100.0f * DELTA;
    }*/
    Sun->rotation.y += 60.0f * TORADIAN * DELTA;
    //Sun->Find("SunBone2")->rotation.y += 60.0f * TORADIAN * DELTA;

    Cam->Update();
    Grid->Update();
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
	App.InitWidthHeight(1800.0f, 900.0f);
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