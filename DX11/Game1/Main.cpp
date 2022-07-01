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
    App.fixFrame = 10000;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int idx = 2 * i + j;
            Cam[idx] = new Camera();
            Cam[idx]->w = 900.0f;
            Cam[idx]->h = 450.0f;
            Cam[idx]->x = j * 900.0f;
            Cam[idx]->y = i * 450.0f;
        }
    }

    Cam[2]->position = Vector3(0.0f, 0.0f, -7.0f);
    Cam[3]->position = Vector3(0.0f, 0.0f, 7.0f);
    Cam[3]->rotation.y = 3.14f;

    Cam[0]->position = Vector3(0.0f, 0.0f, -7.0f);
    Cam[0]->rotation.z = 3.14f;

    Cam[1]->position = Vector3(0.0f, 0.0f, 7.0f);
    Cam[1]->rotation.z = 3.14f;
    Cam[1]->rotation.y = 3.14f;

    //
    Sun = Actor::Create();
    Sun->position.x = 0.0f;
    Sun->position.y = 0.0f;
    Sun->scale.x = 1.0f;
    Sun->scale.y = 1.0f;

    GameObject*	SunBone[5];
    GameObject*	Planet[5];
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
    RESOURCE->ReleaseAll();
}

void Main::Release()
{
	
}


void Main::Update()
{
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Sun->RenderImGui();
    ImGui::End();

    ImGui::Checkbox("Button Enable", &checkbox);
    if (ImGui::Button("UP DOWN") && checkbox)
        Sun->rotation.x += 180.0f * TORADIAN;
    if (ImGui::Button("LEFT RIGHT") && checkbox)
        Sun->rotation.y += 180.0f * TORADIAN;

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
    //Sun->rotation.y += 60.0f * TORADIAN * DELTA;
    Sun->Find("SunBone2")->rotation.y += 60.0f * TORADIAN * DELTA;

    for (int i = 0; i < 4; i++)
    {
        Cam[i]->Update();
    }
    Sun->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (int i = 0; i < 4; i++)
    {
        Cam[i]->Set();
        Sun->Render();
    }
}

void Main::ResizeScreen()
{

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