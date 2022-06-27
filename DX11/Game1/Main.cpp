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
    Sun.position.x = 0.0f;
    Sun.position.y = 0.0f;

    Sun.scale.x = 1.0f;
    Sun.scale.y = 1.0f;

    for (int i = 0; i < 5; i++)
    {
        Sun.children.push_back(&SunBone[i]);
        SunBone[i].parent = &Sun;

        SunBone[i].children.push_back(&Planet[i]);
        Planet[i].parent = &SunBone[i];

        Planet[i].position.x = 2.0f * (i + 1);
        Planet[i].position.y = 2.0f * (i + 1);

        Planet[i].scale.x = 1.0f;
        Planet[i].scale.y = 1.0f;
    }
}

void Main::Release()
{
	
}


void Main::Update()
{
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
    Sun.rotation.y += 60.0f * TORADIAN * DELTA;

    for (int i = 0; i < 4; i++)
    {
        Cam[i]->Update();
    }
    Sun.Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (int i = 0; i < 4; i++)
    {
        Cam[i]->Set();
        Sun.Render();
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