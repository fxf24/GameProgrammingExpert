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

	UI = Actor::Create();
	UI->LoadFile("Window.xml");
	ResizeScreen();
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
}

void Main::LateUpdate()
{
	Vector3 Mouse = INPUT->position;

	Mouse.x -= Cam->viewport.x;
	Mouse.y -= Cam->viewport.y;
	Vector2 MousePos;

	//ndc로의 변환
	MousePos.x = ((2.0f * Mouse.x) / Cam->viewport.width - 1.0f);
	MousePos.y = ((-2.0f * Mouse.y) / Cam->viewport.height + 1.0f);

	if (INPUT->KeyDown(VK_LBUTTON))
	{
		if (UI == nullptr) return;
		cout << MousePos.x << " : " << MousePos.y << endl;
		cout << UI->Find("max")->GetWorldPos().x << " : " << UI->Find("max")->GetWorldPos().y << endl;
		cout << UI->scale.x << " : " << UI->scale.y << endl;
		cout << UI->Find("max")->scale.x << " : " << UI->Find("max")->scale.y << endl;

		Vector2 maxLeftTop = Vector2(UI->Find("max")->GetWorldPos().x - (UI->scale.x * UI->Find("max")->scale.x) / 2,
			UI->Find("max")->GetWorldPos().y + (UI->scale.y * UI->Find("max")->scale.y) / 2);

		Vector2 maxRightBottom = Vector2(UI->Find("max")->GetWorldPos().x + (UI->scale.x * UI->Find("max")->scale.x) / 2,
			UI->Find("max")->GetWorldPos().y - (UI->scale.y * UI->Find("max")->scale.y) / 2);

		Vector2 xLeftTop = Vector2(UI->Find("x")->GetWorldPos().x - (UI->scale.x * UI->Find("x")->scale.x) / 2,
			UI->Find("x")->GetWorldPos().y + (UI->scale.y * UI->Find("x")->scale.y) / 2);

		Vector2 xRightBottom = Vector2(UI->Find("x")->GetWorldPos().x + (UI->scale.x * UI->Find("x")->scale.x) / 2,
			UI->Find("x")->GetWorldPos().y - (UI->scale.y * UI->Find("x")->scale.y) / 2);

		if (MousePos.x >= maxLeftTop.x && MousePos.x <= maxRightBottom.x && MousePos.y <= maxLeftTop.y && MousePos.y >= maxRightBottom.y)
		{
			cout << "in" << endl;

			if (!max)
			{
				UI->Find("max")->material->LoadFile("min.mtl");
				UI->scale.x = 2.0f;
				UI->scale.y = 2.0f;
				UI->SetWorldPos(Vector3(0, 0, 0));
				max = true;
			}
			else
			{
				UI->Find("max")->material->LoadFile("max.mtl");
				UI->scale.x = 1.0f;
				UI->scale.y = 1.0f;
				max = false;
			}
		}

		if (MousePos.x >= xLeftTop.x && MousePos.x <= xRightBottom.x && MousePos.y <= xLeftTop.y && MousePos.y >= xRightBottom.y)
		{
			UI = nullptr;
		}
	}

	if (INPUT->KeyPress(VK_LBUTTON))
	{
		if (UI == nullptr) return;
		Vector2 LeftTop = Vector2(UI->GetWorldPos().x - (UI->scale.x) / 2,
			UI->GetWorldPos().y + (UI->scale.y) / 2);

		Vector2 RightBottom = Vector2(UI->GetWorldPos().x + (UI->scale.x) / 2,
			UI->GetWorldPos().y - (UI->scale.y) / 2);

		if (MousePos.x >= LeftTop.x && MousePos.x <= RightBottom.x && MousePos.y <= LeftTop.y && MousePos.y >= RightBottom.y)
		{
			
			Vector3 move;
			move.x = INPUT->movePosition.x * 0.002f;
			move.y = -INPUT->movePosition.y * 0.002f;
			UI->MoveWorldPos(move);
		}
	}
	
}

void Main::Render()
{
	Cam->Set();

	Grid->Render();

	if (UI != nullptr)
		UI->Render();
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
