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

	ImGui::Text("Mouse X: %f Y: %f", INPUT->NDCPosition.x, INPUT->NDCPosition.y);
}

void Main::LateUpdate()
{
	float left, right, top, bottom;
	if (UI != nullptr)
	{
		left = UI->GetWorldPos().x - UI->S._11 * 0.5;
		right = UI->GetWorldPos().x + UI->S._11 * 0.5;
		top = UI->GetWorldPos().y + UI->S._22 * 0.5;
		bottom = UI->GetWorldPos().y - UI->S._22 * 0.5;

		if (left <= INPUT->NDCPosition.x and right >= INPUT->NDCPosition.x and bottom <= INPUT->NDCPosition.y and top >= INPUT->NDCPosition.y)
		{
			if (INPUT->KeyPress(VK_LBUTTON))
			{
				Vector3 move = INPUT->NDCPosition - PrevMouse;

				if (left + 0.02 >= INPUT->NDCPosition.x)
				{
					UI->scale.x -= move.x * 2;
				}
				else if (right - 0.02 <= INPUT->NDCPosition.x)
				{
					UI->scale.x += move.x * 2;
				}
				else if (bottom + 0.02 >= INPUT->NDCPosition.y)
				{
					UI->scale.y -= move.y * 2;
				}
				else if (top - 0.02 <= INPUT->NDCPosition.y)
				{
					UI->scale.y += move.y * 2;

				}
				else 
				{
					UI->MoveWorldPos(move);	
				}
			}
		}
	}
	
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		if (UI == nullptr) return;

		Vector2 maxLeftTop = Vector2(UI->Find("max")->GetWorldPos().x - UI->Find("max")->S._11 / 2,
			UI->Find("max")->GetWorldPos().y + UI->Find("max")->S._22 / 2);

		Vector2 maxRightBottom = Vector2(UI->Find("max")->GetWorldPos().x + UI->Find("max")->S._11 / 2,
			UI->Find("max")->GetWorldPos().y - UI->Find("max")->S._22 / 2);

		Vector2 xLeftTop = Vector2(UI->Find("x")->GetWorldPos().x - UI->Find("max")->S._11 / 2,
			UI->Find("x")->GetWorldPos().y + UI->Find("max")->S._22 / 2);

		Vector2 xRightBottom = Vector2(UI->Find("x")->GetWorldPos().x + UI->Find("max")->S._11 / 2,
			UI->Find("x")->GetWorldPos().y - UI->Find("max")->S._22 / 2);

		if (INPUT->NDCPosition.x >= maxLeftTop.x && INPUT->NDCPosition.x <= maxRightBottom.x && INPUT->NDCPosition.y <= maxLeftTop.y && INPUT->NDCPosition.y >= maxRightBottom.y)
		{
			if (!max)
			{
				UI->Find("min")->visible = true;
				UI->scale.x = 2.0f;
				UI->scale.y = 2.0f;
				UI->SetWorldPos(Vector3(0, 0, 0));
				max = true;
			}
			else
			{
				UI->Find("min")->visible = false;
				UI->scale.x = 1.0f;
				UI->scale.y = 1.0f;
				max = false;
			}
		}

		if (INPUT->NDCPosition.x >= xLeftTop.x && INPUT->NDCPosition.x <= xRightBottom.x && INPUT->NDCPosition.y <= xLeftTop.y && INPUT->NDCPosition.y >= xRightBottom.y)
		{
			UI->visible = false;
		}
	}

	
	PrevMouse = INPUT->NDCPosition;
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
