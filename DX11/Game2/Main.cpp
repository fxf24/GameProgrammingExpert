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
	SOUND->AddSound("FloralLife.mp3", "BGM", true);
	SOUND->AddSound("gold.wav", "GOLD", false);

	SOUND->Play("BGM");

	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	_Shop = Actor::Create();
	_Shop->LoadFile("Sphere.xml");


	inv.Init();
	store.Init(&inv);
	ResizeScreen();
}

void Main::Release()
{
	
}


void Main::Update()
{
	if (ImGui::Button("BGM Play"))
	{
		SOUND->Play("BGM");
	}
	ImGui::SameLine();
	if (ImGui::Button("BGM Stop"))
	{
		SOUND->Stop("BGM");
	}
	ImGui::SameLine();
	if (ImGui::Button("BGM Pause"))
	{
		SOUND->Pause("BGM");
	}
	ImGui::SameLine();
	if (ImGui::Button("BGM Resume"))
	{
		SOUND->Resume("BGM");
	}
	if (ImGui::SliderFloat("BGM SetVolume", &bgmscale, 0.0f, 1.0f))
	{
		SOUND->SetVolume("BGM", bgmscale);
	}

	if (ImGui::Button("GOLD Play"))
	{
		SOUND->Stop("GOLD");
		SOUND->Play("GOLD");
	}
	ImGui::SameLine();
	if (ImGui::Button("GOLD Stop"))
	{
		SOUND->Stop("GOLD");
	}
	ImGui::SameLine();
	if (ImGui::Button("GOLD Pause"))
	{
		SOUND->Pause("GOLD");
	}
	ImGui::SameLine();
	if (ImGui::Button("GOLD Resume"))
	{
		SOUND->Resume("GOLD");
	}
	if (ImGui::SliderFloat("GOLD SetVolume", &goldscale, 0.0f, 1.0f))
	{
		SOUND->SetVolume("GOLD", goldscale);
	}

	Camera::ControlMainCam();
	
	ImGui::Begin("Hierarchy");
	_Shop->RenderHierarchy();
	Cam->RenderHierarchy();
	ImGui::End();

	Cam->Update();
	Grid->Update();
	
	inv.Update();
	store.Update();

	_Shop->Update();

	ImGui::Text("Mouse  X: %f Y: %f", INPUT->NDCPosition.x,
		INPUT->NDCPosition.y);
}

void Main::LateUpdate()
{
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
		Vector3 Hit;

		if (_Shop->collider->Intersect(Mouse, Hit))
		{
			inv.show = not inv.show;
			store.show = not store.show;
		}
	}
}

void Main::Render()
{
	Cam->Set();
	
	_Shop->Render();
	Grid->Render();
	//깊이 렌더링 끄고 그리는 순서에따라 렌더링
	

	
	// World
	Vector4 Top;
	Top.x = _Shop->GetWorldPos().x;
	Top.y = _Shop->GetWorldPos().y + 2.0f;
	Top.z = _Shop->GetWorldPos().z;
	Top.w = 1.0f;

	// View
	Top = Vector4::Transform(Top, Cam->view);

	float Depth = App.GetWidth() / Top.z;
	Top = Vector4::Transform(Top, Cam->proj);

	//NDC
	Top.x /= Top.w;
	Top.y /= Top.w;	

	//Screen
	Top.x = (Top.x + 1.0f) * App.GetHalfWidth();
	Top.y = (-Top.y + 1.0f) * App.GetHalfHeight();

	Top.x -= Depth * 0.5f * 2.0f;
	Top.y -= Depth * 0.5f;



	RECT rc{ Top.x, Top.y, Top.x + 1000, Top.y + 1000};
	//                    출력할 문자열,텍스트박스 크기위치

	if (Top.z != 0)
		DWRITE->RenderText(L"상점", rc, Depth, L"돋움체", Color(1, 0, 0, 1),
		DWRITE_FONT_WEIGHT_BOLD);

	inv.Render();
	store.Render();
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
