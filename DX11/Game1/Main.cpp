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

    Cam->x = 0;
    Cam->y = 0;

    Cam->w = 1800.0f;
    Cam->h = 900.0f;

    Cam->position = Vector3(0.0f, 0.0f, -10.0f);

    Sun.position.x = 0.0f;
    Sun.position.y = 0.0f;
    Sun.position.z = -0.5f;


    Sun.scale.x = 1.0f;
    Sun.scale.y = 1.0f;


    Planet[0].position.x = -0.5f;
    Planet[0].position.y = 0.0f;
    Planet[0].position.z = 0.0f;
    

    Planet[0].scale.x = 1.0f;
    Planet[0].scale.y = 1.0f;

    Planet[0].rotation.y = 90.0f * TORADIAN;

    Planet[1].position.x = 0.5f;
    Planet[1].position.y = 0.0f;
    Planet[1].position.z = 0.0f;
           
    Planet[1].scale.x = 1.0f;
    Planet[1].scale.y = 1.0f;
           
    Planet[1].rotation.y = -90.0f * TORADIAN;

    Planet[2].position.x = 0.0f;
    Planet[2].position.y = 0.0f;
    Planet[2].position.z = 0.5f;
           
    Planet[2].scale.x = 1.0f;
    Planet[2].scale.y = 1.0f;
           
    Planet[2].rotation.y = -180.0f * TORADIAN;

    Planet[3].position.x = 0.0f;
    Planet[3].position.y = -0.5f;
    Planet[3].position.z = 0.0f;
           
    Planet[3].scale.x = 1.0f;
    Planet[3].scale.y = 1.0f;
           
    Planet[3].rotation.x = -90.0f * TORADIAN;

    Planet[4].position.x = 0.0f;
    Planet[4].position.y = 0.5f;
    Planet[4].position.z = 0.0f;
           
    Planet[4].scale.x = 1.0f;
    Planet[4].scale.y = 1.0f;
           
    Planet[4].rotation.x = 90.0f * TORADIAN;

}

void Main::Release()
{
	
}


void Main::Update()
{
    if (INPUT->KeyPress('1'))
    {
        Cam->fov += 3.14f * DELTA;
    }
    if (INPUT->KeyPress('2'))
    {
        Cam->fov -= 3.14f * DELTA;
    }

    if (INPUT->KeyPress('A'))
    {
        Cam->position += -Cam->GetRight() * 10.0f * DELTA;
    }
    if (INPUT->KeyPress('D'))
    {
        Cam->position += Cam->GetRight() * 10.0f * DELTA;
    }
    if (INPUT->KeyPress('W'))
    {
        Cam->position += Cam->GetUp() * 10.0f * DELTA;
    }
    if (INPUT->KeyPress('S'))
    {
        Cam->position += -Cam->GetUp() * 10.0f * DELTA;
    }
    if (INPUT->KeyPress('Q'))
    {
        Cam->position += Cam->GetForward() * 10.0f * DELTA;
    }
    if (INPUT->KeyPress('E'))
    {
        Cam->position += -Cam->GetForward() * 10.0f * DELTA;
    }
    if (INPUT->KeyPress('I'))
    {
        Cam->rotation.x -= 1.0f * DELTA;
    }
    if (INPUT->KeyPress('K'))
    {
        Cam->rotation.x += 1.0f * DELTA;
    }
    if (INPUT->KeyPress('J'))
    {
        Cam->rotation.y -= 1.0f * DELTA;
    }
    if (INPUT->KeyPress('L'))
    {
        Cam->rotation.y += 1.0f * DELTA;
    }

    Cam->Update();
    for (int i = 0; i < 5; i++)
    {
        Planet[i].Update();
    }
    Sun.Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    Cam->Set();
    for (int i = 0; i < 5; i++)
    {
        Planet[i].Render();
    }
    Sun.Render();
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