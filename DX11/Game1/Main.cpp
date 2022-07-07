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
    Grid->Load("Grid.xml");
    Sun = Actor::Create();
    Sun->Load("CubeMan.xml");

    state = true;
    neckSwing = 0.0f;
    armLegSwing = 0.0f;
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
    ImGui::Begin("Hierarchy");
    Sun->RenderHierarchy();
    Grid->RenderHierarchy();
    ImGui::End();

    if (INPUT->KeyPress(VK_UP))
    {
        Sun->Find("Body")->position -= Sun->GetForward() * DELTA * 10.0f;
       
        Sun->Find("LLegJoint")->rotation.x = sinf(armLegSwing * TORADIAN) / 4.0f;
        Sun->Find("RLegJoint")->rotation.x = -sinf(armLegSwing * TORADIAN) / 4.0f;
        Sun->Find("LSholder")->rotation.x = -sinf(armLegSwing * TORADIAN) / 4.0f;
        Sun->Find("RSholder")->rotation.x = sinf(armLegSwing * TORADIAN) / 4.0f;
        armLegSwing += DELTA * 500.0f;
        Sun->Find("Neck")->rotation.y = 0.0f;
        state = false;
    }
    else if (INPUT->KeyPress(VK_DOWN))
    {
        Sun->Find("Body")->position += Sun->GetForward() * DELTA * 10.0f;

        Sun->Find("LLegJoint")->rotation.x = sinf(armLegSwing * TORADIAN) / 4.0f;
        Sun->Find("RLegJoint")->rotation.x = -sinf(armLegSwing * TORADIAN) / 4.0f;
        Sun->Find("LSholder")->rotation.x = -sinf(armLegSwing * TORADIAN) / 4.0f;
        Sun->Find("RSholder")->rotation.x = sinf(armLegSwing * TORADIAN) / 4.0f;
        armLegSwing += DELTA * 500.0f;
        Sun->Find("Neck")->rotation.y = 0.0f;
        state = false;
    }
    else 
        state = true;

    if (INPUT->KeyPress(VK_LEFT))
    {
        Sun->Find("Body")->rotation.y -= 1.0f * TORADIAN;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        Sun->Find("Body")->rotation.y += 1.0f * TORADIAN;
    }

    if (state)
    {
        Sun->Find("Neck")->rotation.y = sinf(neckSwing * 1.0f * TORADIAN) / 3.0f;
        neckSwing += DELTA * 500.0f;
        Sun->Find("LLegJoint")->rotation.x = 0.0f;
        Sun->Find("RLegJoint")->rotation.x = 0.0f;
        Sun->Find("LSholder")->rotation.x = 0.0f;
        Sun->Find("RSholder")->rotation.x = 0.0f;
    }

    //swing = 0.0f;
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