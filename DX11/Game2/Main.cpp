#include "stdafx.h"
#include "Main.h"

Blur blur;

Main::Main()
{
}
Main::~Main()
{
}

void Main::Init()
{

	SCENE->AddScene("SC1", new Scene1());
	SCENE->AddScene("SC2", new Scene2());
	//SCENE->AddScene("LOADING", new Scene1());
	SCENE->ChangeScene("SC1")->Init();
	BLUR->blur.blendColor.x = 0.0f;
	BLUR->blur.blendColor.y = 0.0f;
	BLUR->blur.blendColor.z = 0.0f;
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
void Main::PreRender()
{
	SCENE->PreRender();
}
void Main::Render()
{
	SCENE->Render();

	BLUR->Set();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();

	if (RT)
	{
		RT->ResizeScreen(Cam->viewport.width, Cam->viewport.height);
	}
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game2");
	App.SetInstance(instance);
	WIN->Create();
	D3D->Create();
	Main* main = new Main();
	main->Init();
	int wParam = (int)WIN->Run(main);
	main->Release();
	SafeDelete(main);
	D3D->DeleteSingleton();
	WIN->DeleteSingleton();
	return wParam;
}
