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
	
}

void Main::Release()
{
	
}


void Main::Update()
{
}

void Main::LateUpdate()
{
}
void Main::Render()
{
}

void Main::ResizeScreen()
{

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
