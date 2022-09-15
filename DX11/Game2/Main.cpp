#include "stdafx.h"
#include "Main.h"
Main::Main()
{
}
Main::~Main()
{
}

//struct A
//{
//	string name = "name";
//	void Print()
//	{
//		cout << name << endl;
//	}
//};
//
//A a;

void Main::Init()
{
	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");


	inv.Init();



	/*Ui->mouseOver = [](){ cout << "MouseOver"<<endl; };
	Ui->mouseDown = [](){ };
	Ui->mousePress = bind(&A::Print, &a );
	Ui->mouseUp = []() { cout << "mouseUp" << endl; };*/

	//Ui->scale.x = 2;
	//Ui->scale.y = 2;

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
	Camera::ControlMainCam();
	
	//ImGui::Begin("Hierarchy");
	////Ui->RenderHierarchy();
	//ImGui::End();


	Cam->Update();
	Grid->Update();
	inv.Update();

	ImGui::Text("Mouse  X: %f Y: %f", INPUT->NDCPosition.x,
		INPUT->NDCPosition.y);

}

void Main::LateUpdate()
{

	/*float left = Ui->GetWorldPos().x - Ui->S._11 * 0.5f;
	float right = Ui->GetWorldPos().x + Ui->S._11 * 0.5f;
	float top = Ui->GetWorldPos().y + Ui->S._22 * 0.5f;
	float bottom = Ui->GetWorldPos().y - Ui->S._22 * 0.5f;

	if (left < INPUT->NDCPosition.x and INPUT->NDCPosition.x < right
		and bottom < INPUT->NDCPosition.y and
		INPUT->NDCPosition.y < top)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			Vector3 mov = INPUT->NDCPosition - PrevMouse;
			Ui->MoveWorldPos(mov * 0.5f);
			Ui->scale.x += mov.x;
		}
	}*/

	

	//PrevMouse = INPUT->NDCPosition;
}
void Main::Render()
{
	Cam->Set();
	
	Grid->Render();
	//±íÀÌ ·»´õ¸µ ²ô°í ±×¸®´Â ¼ø¼­¿¡µû¶ó ·»´õ¸µ
	
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
