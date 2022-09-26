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
		if (Util::RayIntersectTriNear(Mouse, Shop, Hit))
		{
			cout << "Shop ����" << endl;
			inv.SetVisible();
		}
	}
}

void Main::Render()
{
	Cam->Set();
	
	Shop->Render();
	Grid->Render();
	//���� ������ ���� �׸��� ���������� ������
	
	inv.Render();
	
	Matrix temp = Shop->W * Cam->view * Cam->proj;
	Vector4 pos = Vector4(temp._41, temp._42, temp._43, temp._44);
	pos.Normalize();
	pos.x *= App.GetWidth();
	pos.y *= App.GetHeight();

	RECT rc{ pos.x, pos.y, pos.x + 100, pos.y + 100 };
	//                    ����� ���ڿ�,�ؽ�Ʈ�ڽ� ũ����ġ

	DWRITE->RenderText(L"����", rc, 30, L"Verdana", Color(1, 0, 0, 1),
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
