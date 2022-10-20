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
	Cam->LoadFile("BirdCam.xml");
	Camera::main = Cam;

	for (int i = 0; i < 20; i++)
	{
		Wall[i] = Actor::Create();
		Wall[i]->LoadFile("BirdWall.xml");
	}
	

	cubeMan = new CubeMan();

	popup = UI::Create();
	popup->LoadFile("message.xml");
	popup->visible = false;

	ResizeScreen();
}


void Main::Release()
{


}

void Main::Update()
{
	time += DELTA;
	//Camera::ControlMainCam();
	LIGHT->RenderDetail();

	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	Cam->RenderHierarchy();
	sky->RenderHierarchy();
	cubeMan->RenderHierarchy();
	ImGui::End();

	Cam->Update();
	sky->Update();
	popup->Update();


	for (int i = 0; i < 20; i++)
	{
		Wall[i]->Update();
		if (Wall[i]->visible && !fail)
		{
			Wall[i]->MoveWorldPos(Vector3(0, 0, speed * DELTA));
			
			if (Wall[i]->GetWorldPos().z > 200)
			{
				Wall[i]->visible = false;
				Wall[i]->SetWorldPosZ(-200);
			}
		}
	}
	
	if (!fail)
		cubeMan->Update();

	if (time >= 3.0f && !fail)
	{
		std::random_device rd;

		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(cubeMan->GetWorldPos().y - 30, cubeMan->GetWorldPos().y + 70);

		for (int i = 0; i < 20; i++)
		{
			if (!Wall[i]->visible)
			{
				Wall[i]->visible = true;
				Wall[i]->SetWorldPosY(dis(gen));
				break;
			}
		}

		time = 0;
		score += 10;
	}

	
}

void Main::LateUpdate()
{
	for (int i = 0; i < 20; i++)
	{
		if (Wall[i]->visible)
		{
			for (auto it = Wall[i]->children.begin(); it != Wall[i]->children.end(); it++)
			{
				if (it->second->collider->Intersect(cubeMan->collider))
				{
					cout << "hit" << endl;
					fail = true;
					popup->visible = true;
				}
			}
		}
	}
	
	if (cubeMan->GetWorldPos().y < -180)
	{
		fail = true;
		popup->visible = true;
	}
}

void Main::Render()
{
	LIGHT->Set();
	Cam->Set();
	sky->Render();
	cubeMan->Render();

	for (int i = 0; i < 20; i++)
	{
		Wall[i]->Render();
	}

	DEPTH->Set(false);
	popup->Render();
	DEPTH->Set(true);

	RECT rc{ 0,0, 1000, 100 };
	//                    출력할 문자열,텍스트박스 크기위치

	string sc = "Score : " + to_string(score);
	wstring wstr;
	wstr.assign(sc.begin(), sc.end());
	DWRITE->RenderText(wstr, rc, 30, L"Verdana", Color(1, 0, 0, 1),
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
	App.SetAppName(L"PlappyBird");
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
