#include "stdafx.h"
#include "Main.h"
Main::Main()
{
}
Main::~Main()
{
}

struct A
{
	string name = "name";
	void Print()
	{
		cout << name << endl;
	}
};

A a;
void Main::Init()
{
	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	UI = UI::Create();
	UI->LoadFile("Window.xml");

	/*UI->mouseOver = []() {cout << "MouseOver" << endl; };
	UI->mouseDown = []() {cout << "MouseDown" << endl; };
	UI->mousePress = bind(&A::Print, &a);
	UI->mouseUp = []() {cout << "MouseUp" << endl; };*/

	ResizeScreen();

	UI->mouseDown = [&]() {PrevMouse = INPUT->NDCPosition; };
	UI->mousePress = bind(&Main::Resize, this);
}


void Main::Resize()
{
	float left, right, top, bottom;

	left = UI->GetWorldPos().x - UI->S._11 * 0.5;
	right = UI->GetWorldPos().x + UI->S._11 * 0.5;
	top = UI->GetWorldPos().y + UI->S._22 * 0.5;
	bottom = UI->GetWorldPos().y - UI->S._22 * 0.5;
	Vector3 move = INPUT->NDCPosition - PrevMouse;


	/*UI->MoveWorldPos(move * 0.5f);
	UI->scale.x += move.x;*/
	
	if (left + 0.02 >= INPUT->NDCPosition.x)
	{   
		UI->MoveWorldPos(move * 0.5f);
		UI->scale.x -= move.x;
	}
	if (right - 0.02 <= INPUT->NDCPosition.x)
	{
		UI->MoveWorldPos(move * 0.5f);
		UI->scale.x += move.x;
	}
	if (bottom + 0.02 >= INPUT->NDCPosition.y)
	{
		UI->MoveWorldPos(move * 0.5f);
		UI->scale.y -= move.y;
	}
	if (top - 0.02 <= INPUT->NDCPosition.y)
	{
		UI->MoveWorldPos(move * 0.5f);
		UI->scale.y += move.y;
	}
	
	
	PrevMouse = INPUT->NDCPosition;



}

void Main::Release()
{
	
}


void Main::Update()
{
	Camera::ControlMainCam();

	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	Grid->RenderHierarchy();
	Cam->RenderHierarchy();
	if (UI != nullptr)
		UI->RenderHierarchy();
	ImGui::End();

	Cam->Update();
	Grid->Update();
	if (UI != nullptr)
		UI->Update();

	ImGui::Text("Mouse X: %f Y: %f", INPUT->NDCPosition.x, INPUT->NDCPosition.y);
}



void Main::LateUpdate()
{
	
}

void Main::Render()
{
	Cam->Set();

	Grid->Render();

	// ±íÀÌ ·»´õ¸µ ²ô°í ±×¸®´Â ¼ø¼­¿¡µû¶ó ·»´õ¸µ
	DEPTH->Set(false);
	if (UI != nullptr)
		UI->Render();
	DEPTH->Set(true);
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
