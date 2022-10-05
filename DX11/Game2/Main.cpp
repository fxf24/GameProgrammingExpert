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

	//SOUND->AddSound("bgm.wav", "BGM", true);
	//SOUND->AddSound("gun.wav", "GUN", false);

	//SOUND->Play("BGM");
	sky = Sky::Create();
	sky->LoadFile("Sky.xml");
	Map = Actor::Create();
	Map->LoadFile("Map.xml");


	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	_Shop = Actor::Create();

	_Shop->LoadFile("Sphere.xml");

	inv.Init();
	shop.Init(&inv);



	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();
}

void Main::Release()
{

}

void Main::Update()
{
	
	Camera::ControlMainCam();
	
	//ImGui::Begin("Hierarchy");
	////Ui->RenderHierarchy();
	//ImGui::End();

	_Shop->RenderHierarchy();
	Cam->RenderHierarchy();
	sky->RenderHierarchy();
	ImGui::SliderFloat("hp bar", &_Shop->Find("None")->scale.x, -1.0f, 1.0f);


	Cam->Update();
	Grid->Update();
	_Shop->Update();
	Map->Update();
	inv.Update();
	shop.Update();
	sky->Update();

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
	Cam->Set();
	Grid->Render();
	Map->Render();
	sky->Render();

	// World
	Vector4 Top;
	Top.x = _Shop->GetWorldPos().x;
	Top.y = _Shop->GetWorldPos().y + 3.5f;
	Top.z = _Shop->GetWorldPos().z;
	Top.w = 1.0f;
	// View
	Top = Vector4::Transform(Top, Cam->view);

	float Depth = 1280.0f / Top.z;

	Top = Vector4::Transform(Top, Cam->proj);

	//NDC
	Top.x /= Top.w;
	Top.y /= Top.w;


	//Screen
	Top.x = (Top.x + 1.0f )* App.GetHalfWidth();
	//       
	Top.y = (-Top.y + 1.0f )* App.GetHalfHeight();
	Top.x -= Depth * 0.66f * 2.0f;
	Top.y -= Depth * 0.66f;

	//깊이 렌더링  off
	//         l  t  r   b
	RECT rc{ Top.x,Top.y,Top.x + 10000,Top.y + 10000 };
	//                    출력할 문자열,텍스트박스 크기위치
	if (Depth > 1)
		DWRITE->RenderText(L"SHOP", rc, Depth,L"Verdana",Color(1,0,0,1));
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
