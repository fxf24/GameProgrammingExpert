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
	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	Shop = Actor::Create();
	Shop->LoadFile("Sphere.xml");


	inv.Init();

	ResizeScreen();
}

void Main::Release()
{
	
}


void Main::Update()
{
	Camera::ControlMainCam();
	
	ImGui::Begin("Hierarchy");
	Shop->RenderHierarchy();
	Cam->RenderHierarchy();
	ImGui::End();

	Cam->Update();
	Grid->Update();
	
	inv.Update();

	Shop->Update();

	ImGui::Text("Mouse  X: %f Y: %f", INPUT->NDCPosition.x,
		INPUT->NDCPosition.y);
}

void Main::LateUpdate()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
		Vector3 Hit;

		if (Shop->collider->Intersect(Mouse, Hit))
		{
			inv.show = not inv.show;
		}
	}
}

void Main::Render()
{
	Cam->Set();
	
	Shop->Render();
	Grid->Render();
	//깊이 렌더링 끄고 그리는 순서에따라 렌더링
	
	inv.Render();
	
	// World
	Vector4 Top;
	Top.x = Shop->GetWorldPos().x;
	Top.y = Shop->GetWorldPos().y;
	Top.z = Shop->GetWorldPos().z;
	Top.w = 1.0f;

	// View
	Top = Vector4::Transform(Top, Cam->view);

	Top = Vector4::Transform(Top, Cam->proj);

	//NDC
	Top.x /= Top.w;
	Top.y /= Top.w;

	Top.x -= 0.05f;
	Top.y += 0.2f;

	//Screen
	Top.x = (Top.x + 1.0f) * App.GetHalfWidth();
	Top.y = (-Top.y + 1.0f) * App.GetHalfHeight();

	RECT rc{ Top.x, Top.y, Top.x + 1000, Top.y + 1000};
	//                    출력할 문자열,텍스트박스 크기위치

	DWRITE->RenderText(L"상점", rc, 30, L"Verdana", Color(1, 0, 0, 1),
		DWRITE_FONT_WEIGHT_BOLD);
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
