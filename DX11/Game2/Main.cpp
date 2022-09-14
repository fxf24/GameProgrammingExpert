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


	inv.Init();

	/*UI->mouseOver = []() {cout << "MouseOver" << endl; };
	UI->mouseDown = []() {cout << "MouseDown" << endl; };
	UI->mousePress = bind(&A::Print, &a);
	UI->mouseUp = []() {cout << "MouseUp" << endl; };*/

	ResizeScreen();

	/*UI->mouseDown = bind(&Main::ClickEvent, this);
	UI->mousePress = bind(&Main::Resize, this);
	UI->mouseUp = bind(&Main::UpEvent, this);*/
}


//void Main::Resize()
//{
//	float left, right, top, bottom;
//
//	left = UI->GetWorldPos().x - UI->S._11 * 0.5;
//	right = UI->GetWorldPos().x + UI->S._11 * 0.5;
//	top = UI->GetWorldPos().y + UI->S._22 * 0.5;
//	bottom = UI->GetWorldPos().y - UI->S._22 * 0.5;
//	Vector3 move = INPUT->NDCPosition - PrevMouse;
//
//
//	/*UI->MoveWorldPos(move * 0.5f);
//	UI->scale.x += move.x;*/
//	
//	if (top - 0.05 <= INPUT->NDCPosition.y and right - 0.05 <= INPUT->NDCPosition.x)
//	{
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.x += move.x;
//		UI->scale.y += move.y;
//	}
//	else if (top - 0.05 <= INPUT->NDCPosition.y and left + 0.05 >= INPUT->NDCPosition.x)
//	{
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.x -= move.x;
//		UI->scale.y += move.y;
//	}
//	else if (bottom + 0.05 >= INPUT->NDCPosition.y and right - 0.05 <= INPUT->NDCPosition.x)
//	{
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.x += move.x;
//		UI->scale.y -= move.y;
//	}
//	else if (bottom + 0.05 >= INPUT->NDCPosition.y and left + 0.05 >= INPUT->NDCPosition.x)
//	{
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.x -= move.x;
//		UI->scale.y -= move.y;
//	}
//	else if (left + 0.05 >= INPUT->NDCPosition.x)
//	{   
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.x -= move.x;
//	}
//	else if (right - 0.05 <= INPUT->NDCPosition.x)
//	{
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.x += move.x;
//	}
//	else if (bottom + 0.05 >= INPUT->NDCPosition.y)
//	{
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.y -= move.y;
//	}
//	else if (top - 0.05 <= INPUT->NDCPosition.y)
//	{
//		UI->MoveWorldPos(move * 0.5f);
//		UI->scale.y += move.y;
//	}
//	else
//	{
//		if (from != "")
//		{
//			if (!UI->Find(from)->children.empty())
//			{
//				for (auto a : UI->Find(from)->children)
//				{
//					a.second->MoveWorldPos(move);
//				}
//			}
//		}
//		else
//		{
//			UI->MoveWorldPos(move);
//		}
//	}
//
//	PrevMouse = INPUT->NDCPosition;
//}

//void Main::ClickEvent()
//{
//	for (int i = 0; i < 9; i++)
//	{
//		string temp = "inven" + to_string(i + 1);
//		Vector2 LeftTop = Vector2(UI->Find(temp)->GetWorldPos().x - UI->Find(temp)->S._11 / 2,
//			UI->Find(temp)->GetWorldPos().y + UI->Find(temp)->S._22 / 2);
//
//		Vector2 RightBottom = Vector2(UI->Find(temp)->GetWorldPos().x + UI->Find(temp)->S._11 / 2,
//			UI->Find(temp)->GetWorldPos().y - UI->Find(temp)->S._22 / 2);
//
//		if (INPUT->NDCPosition.x >= LeftTop.x && INPUT->NDCPosition.x <= RightBottom.x && INPUT->NDCPosition.y <= LeftTop.y && INPUT->NDCPosition.y >= RightBottom.y)
//		{
//			cout << temp << endl;
//			from = temp;
//		}
//	}
//
//
//	Vector2 maxLeftTop = Vector2(UI->Find("max")->GetWorldPos().x - UI->Find("max")->S._11 / 2,
//		UI->Find("max")->GetWorldPos().y + UI->Find("max")->S._22 / 2);
//
//	Vector2 maxRightBottom = Vector2(UI->Find("max")->GetWorldPos().x + UI->Find("max")->S._11 / 2,
//		UI->Find("max")->GetWorldPos().y - UI->Find("max")->S._22 / 2);
//
//	Vector2 xLeftTop = Vector2(UI->Find("x")->GetWorldPos().x - UI->Find("max")->S._11 / 2,
//		UI->Find("x")->GetWorldPos().y + UI->Find("max")->S._22 / 2);
//
//	Vector2 xRightBottom = Vector2(UI->Find("x")->GetWorldPos().x + UI->Find("max")->S._11 / 2,
//		UI->Find("x")->GetWorldPos().y - UI->Find("max")->S._22 / 2);
//
//	if (INPUT->NDCPosition.x >= maxLeftTop.x && INPUT->NDCPosition.x <= maxRightBottom.x && INPUT->NDCPosition.y <= maxLeftTop.y && INPUT->NDCPosition.y >= maxRightBottom.y)
//	{
//		if (!max)
//		{
//			UI->Find("min")->visible = true;
//			UI->scale.x = 2.0f;
//			UI->scale.y = 2.0f;
//			UI->SetWorldPos(Vector3(0, 0, 0));
//			max = true;
//		}
//		else
//		{
//			UI->Find("min")->visible = false;
//			UI->scale.x = 1.0f;
//			UI->scale.y = 1.0f;
//			max = false;
//		}
//	}
//
//	if (INPUT->NDCPosition.x >= xLeftTop.x && INPUT->NDCPosition.x <= xRightBottom.x && INPUT->NDCPosition.y <= xLeftTop.y && INPUT->NDCPosition.y >= xRightBottom.y)
//	{
//		UI->visible = false;
//	}
//
//	PrevMouse = INPUT->NDCPosition;
//}
//
//void Main::UpEvent()
//{
//	for (int i = 0; i < 9; i++)
//	{
//		string temp = "inven" + to_string(i + 1);
//		Vector2 LeftTop = Vector2(UI->Find(temp)->GetWorldPos().x - UI->Find(temp)->S._11 / 2,
//			UI->Find(temp)->GetWorldPos().y + UI->Find(temp)->S._22 / 2);
//
//		Vector2 RightBottom = Vector2(UI->Find(temp)->GetWorldPos().x + UI->Find(temp)->S._11 / 2,
//			UI->Find(temp)->GetWorldPos().y - UI->Find(temp)->S._22 / 2);
//		
//		if (INPUT->NDCPosition.x >= LeftTop.x && INPUT->NDCPosition.x <= RightBottom.x && INPUT->NDCPosition.y <= LeftTop.y && INPUT->NDCPosition.y >= RightBottom.y)
//		{
//			to = temp;
//		}
//	}
//
//	if (to == "")
//	{
//		if (from != "")
//		{
//			if (!UI->Find(from)->children.empty())
//			{
//				for (auto a : UI->Find(from)->children)
//				{
//					a.second->SetWorldPos(UI->Find(from)->GetWorldPos());
//				}
//			}
//		}		
//	}
//	else
//	{
//		if (!UI->Find(to)->children.empty())
//		{
//			GameObject* temp1 = nullptr;
//			GameObject* temp2 = nullptr;
//			for (auto a : UI->Find(from)->children)
//			{
//				temp1 = a.second;
//			}
//			for (auto b : UI->Find(to)->children)
//			{
//				temp2 = b.second;
//			}
//
//			UI->MoveChild(UI->Find(from), temp2);
//			UI->MoveChild(UI->Find(to), temp1);
//			temp1->SetWorldPos(UI->Find(to)->GetWorldPos());
//			temp2->SetWorldPos(UI->Find(from)->GetWorldPos());
//
//		}
//		else
//		{
//			GameObject* temp = nullptr;
//			if (!UI->Find(from)->children.empty())
//			{
//				for (auto a : UI->Find(from)->children)
//				{
//					temp = a.second;
//				}
//				UI->MoveChild(UI->Find(to), temp);
//				temp->SetWorldPos(UI->Find(to)->GetWorldPos());
//			}	
//		}
//	}
//	from = "";
//	to = "";
//}

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
	inv.Ui->RenderHierarchy();
	ImGui::End();

	Cam->Update();
	Grid->Update();
	inv.Update();

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
	inv.Render();
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
