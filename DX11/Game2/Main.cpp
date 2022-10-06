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

	sky = Sky::Create();


	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	_Shop = Actor::Create();

	_Shop->LoadFile("Sphere.xml");

	inv.Init();
	shop.Init(&inv);

	Map = Actor::Create();
	Map->LoadFile("Map.xml");

	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();

	/*Ui->mouseDown = [&]() {PrevMouse = INPUT->NDCPosition; };
	Ui->mousePress = bind(&Main::Resize, this);*/
}
//void Main::Resize()
//{
//	Vector3 mov = INPUT->NDCPosition - PrevMouse;
//	Ui->MoveWorldPos(mov * 0.5f);
//	Ui->scale.x += mov.x;
//
//	PrevMouse = INPUT->NDCPosition;
//}



void Main::Release()
{

}

void Main::Update()
{
	ImGui::SliderFloat3("dirLight", (float*)(&LIGHT->dirLight.direction),-1,1);
	Camera::ControlMainCam();
	
	//ImGui::Begin("Hierarchy");
	////Ui->RenderHierarchy();
	//ImGui::End();
	sky->RenderHierarchy();
	_Shop->RenderHierarchy();
	Cam->RenderHierarchy();

	Cam->Update();
	Grid->Update();
	_Shop->Update();
	Map->Update();
	sky->Update();
	inv.Update();
	shop.Update();

	ImGui::Text("Mouse  X: %f Y: %f", INPUT->NDCPosition.x,
		INPUT->NDCPosition.y);

}

void Main::LateUpdate()
{
	Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);

	if (INPUT->KeyDown(VK_LBUTTON))
	{
		Vector3 Hit;
		if (_Shop->collider->Intersect(Mouse, Hit))
		{
			inv.show = not inv.show;
		}
	}
}
void Main::Render()
{
	LIGHT->Set();
	Cam->Set();
	sky->Render();

	Grid->Render();
	Map->Render();
	_Shop->Render();

	inv.Render();
	shop.Render();
}

void Main::ResizeScreen()
{
	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();
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
