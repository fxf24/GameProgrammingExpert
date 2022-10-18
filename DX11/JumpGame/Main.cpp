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
	SOUND->AddSound("bgm.mp3", "BGM", true);
	SOUND->AddSound("fail.mp3", "Fail", false);
	SOUND->AddSound("complete.mp3", "Complete", false);

	SOUND->SetVolume("BGM", 0.1f);
	SOUND->SetVolume("Fail", 0.5f);
	SOUND->SetVolume("Complete", 0.5f);
	sky = Sky::Create();

	Cam = Camera::Create();
	Cam->LoadFile("RunCam.xml");
	Camera::main = Cam;

	Map = Terrain::Create();
	Map->LoadFile("RunMap.xml");

	popup = UI::Create();
	popup->LoadFile("message.xml");
	popup->visible = false;

	cubeMan = new CubeMan();
	cubeManTopRay.direction = Vector3(0, -1, 0);

	lerpValue = 1.0f;

	Map->showNode = false;

	for (int i = 0; i < 120; i++)
	{
		ObjectPool[i] = Actor::Create();
		ObjectPool[i]->LoadFile("Wall.xml");
		ObjectPool[i]->visible = false;

		std::random_device rd;

		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(0, 99);

		int num = dis(gen) % 3;

		if (num == 0)
		{
			ObjectPool[i]->SetWorldPosZ(54.0f);
		}
		else if (num == 1)
		{
			ObjectPool[i]->SetWorldPosZ(-63.0f);
		}
	}

	SOUND->Play("BGM");
	ResizeScreen();
}


void Main::Release()
{
	cubeMan->Release();

}

void Main::Update()
{
	time += DELTA;
	//Camera::ControlMainCam();
	LIGHT->RenderDetail();
	//
	////Ui->RenderHierarchy();
	//
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	Cam->RenderHierarchy();
	sky->RenderHierarchy();
	Map->RenderHierarchy();
	cubeMan->RenderHierarchy();
	popup->RenderHierarchy();
	ImGui::End();

	if (time >= 100.0f / speed && !end)
	{
		time = 0.0f;

		if (max < 120)
			ObjectPool[max++]->visible = true;

		speed += 4.0f;
	}

	Cam->Update();
	sky->Update();
	Map->Update();
	cubeMan->Update();
	popup->Update();


	if (!end)
	{
		for (int i = min; i < max; i++)
		{
			if (ObjectPool[i]->visible)
			{
				ObjectPool[i]->Update();
				float x = (float)(ObjectPool[i]->GetWorldPos().x);
				ObjectPool[i]->SetWorldPosX(x - speed * DELTA);

				if (ObjectPool[i]->GetWorldPos().x < -170.0f)
				{
					ObjectPool[i]->visible = false;
					ObjectPool[i]->SetWorldPosX(140.0f);
					min = i;
				}
			}
		}
	}

	if (min >= 119 && !end)
	{
		end = true;
		SOUND->Stop("BGM");

		SOUND->Play("Complete");
		popup->visible = true;
		popup->material = RESOURCE->materials.Load("complete.mtl");
	}
}

void Main::LateUpdate()
{
    cubeManTopRay.position = cubeMan->GetWorldPos();
    cubeManTopRay.position.y += 1000.0f;
    Vector3 hit;

    if (Util::RayIntersectMap(cubeManTopRay, Map, hit))
    {
        float LastFoot = cubeMan->GetLastPos().y;

        if (LastFoot > hit.y)
        {
            cubeMan->Falling();
            cubeMan->WorldUpdate();
        }
        else if (LastFoot < hit.y)
        {
            cubeMan->Landing();

            if (hit.y - LastFoot < 3.0f)
                cubeMan->SetWorldPosY(hit.y);

            else
            {
                cubeMan->SetWorldPosX(cubeMan->GetLastPos().x);
                cubeMan->SetWorldPosZ(cubeMan->GetLastPos().z);
            }
            cubeMan->WorldUpdate();
        }
    }
    else
    {
        cubeMan->SetWorldPos(cubeMan->GetLastPos());
        cubeMan->WorldUpdate();
    }

	if (INPUT->KeyDown(VK_LEFT) && !end)
	{
		from = cubeMan->GetWorldPos();


		if (Map->PickNode(cubeMan->GetWorldPos()) == 1)
		{
			to = Map->dijkstra.NodeList[2].pos;
		}
		else if (Map->PickNode(cubeMan->GetWorldPos()) == 2)
		{
			to = Map->dijkstra.NodeList[0].pos;
		}
		else
		{
			to = Map->dijkstra.NodeList[0].pos;
		}

		lerpValue = 0.0f;
	}

	if (INPUT->KeyDown(VK_RIGHT) && !end)
	{
		from = cubeMan->GetWorldPos();

		if (Map->PickNode(cubeMan->GetWorldPos()) == 0)
		{
			to = Map->dijkstra.NodeList[2].pos;
		}
		else if (Map->PickNode(cubeMan->GetWorldPos()) == 2)
		{
			to = Map->dijkstra.NodeList[1].pos;
		}
		else
		{
			to = Map->dijkstra.NodeList[1].pos;
		}

		lerpValue = 0.0f;
	}


	if (lerpValue < 1.0f)
	{
		Vector3 coord = Util::Lerp(from, to, lerpValue);
		cubeMan->SetWorldPos(coord);
		Vector3 Dis = from - to;
		lerpValue += DELTA / Dis.Length() * speed;

		Vector3 Hit2;
		if (Util::RayIntersectMap(cubeManTopRay, Map, Hit2))
		{
			cubeMan->SetWorldPosY(Hit2.y);
		}
		else
		{
			cout << "맵밖에있다" << endl;
		}

		if (lerpValue > 1.0f)
		{
			cubeMan->SetWorldPos(to);
		}
	}

	if (!end)
	{
		for (int i = min; i < max; i++)
		{
			if (ObjectPool[i]->visible)
			{
				if (cubeMan->collider->Intersect(ObjectPool[i]->collider))
				{
					cout << "collide" << endl;
					end = true;
					popup->visible = true;
					SOUND->Stop("BGM");
					SOUND->Play("Fail");
				}
			}
		}
	}
	
}
void Main::Render()
{
	LIGHT->Set();
	Cam->Set();
	sky->Render();
	Map->Render();

	for (int i = min; i < max; i++)
	{
		if (ObjectPool[i]->visible)
		{
			ObjectPool[i]->Render();
		}
	}
	
	BLEND->Set(true);
	cubeMan->Render();
	BLEND->Set(false);

	DEPTH->Set(false);
	popup->Render();
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
	App.SetAppName(L"AvoidWall");
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
