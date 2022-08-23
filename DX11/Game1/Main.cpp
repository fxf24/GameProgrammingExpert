#include "stdafx.h"
#include "Main.h"

Main::Main()
{

}

Main::~Main()
{

}

Scene* scene1;
int LoadingCount = 0;

void LoadingScene1()
{
    scene1 = new Scene1();
    scene1->Init();
}

void Main::Init()
{
    //sc1 = new Scene1();
    sc1 = new LoadingScene();
    sc1->Init();
    t1 = new thread(LoadingScene1);
}

void Main::Release()
{
    t1->join();
    delete t1;
    sc1->Release();
}


void Main::Update()
{
    sc1->Update();
}

void Main::LateUpdate()
{
    sc1->LateUpdate();
}

void Main::Render()
{
    sc1->Render();

    if (LoadingCount == 4)
    {
        sc1 = scene1;
    }
}

void Main::ResizeScreen()
{
    sc1->ResizeScreen();
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