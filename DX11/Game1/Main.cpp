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
    //LoadingScene* temp = new LoadingScene();
    //SCENE->AddScene("LOADING", temp);
    SCENE->AddScene("SC1", new Scene1());
    SCENE->AddScene("SC2", new Scene2());
    //SCENE->AddScene("LOADING", new Scene1());
    SCENE->ChangeScene("SC2")->Init();
    /*temp->LoadingTarget("SC1", 4, 
        []()
        { SCENE->GetScene("SC1")->Init(); }
        );*/

}

void Main::Release()
{
    SCENE->Release();
}


void Main::Update()
{
    SCENE->Update();
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
}

void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{
    SCENE->ResizeScreen();
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