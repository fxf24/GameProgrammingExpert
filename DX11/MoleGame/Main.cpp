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
	Cam->LoadFile("moleCam.xml");
	Camera::main = Cam;

	Map = Terrain::Create();
	Map->LoadFile("molefield.xml");
	Map->CreateStructuredBuffer();

	hammer = Actor::Create();
	hammer->LoadFile("hammer.xml");


	for (int i = 0; i < 9; i++)
	{
		string name = "mole" + to_string(i+1);
		moles[i] = Actor::Create(name);
		moles[i]->LoadFile("mole.xml");
		int x = -(i / 3 - 1);
		int z = i % 3 - 1;
		moles[i]->SetLocalPosX(83 * x);
		moles[i]->SetLocalPosZ(83 * -z);
		moles[i]->visible = false;
	}

	for (int i = 0; i < 120; i++)
	{
		std::random_device rd;

		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(0, 8);

		order[i] = dis(gen);
	}

	ResizeScreen();
}


void Main::Release()
{


}

void Main::Update()
{
	time += DELTA;
	Camera::ControlMainCam();
	LIGHT->RenderDetail();

	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	Cam->RenderHierarchy();
	sky->RenderHierarchy();
	Map->RenderHierarchy();
	hammer->RenderHierarchy();
	ImGui::End();

	Cam->Update();
	sky->Update();
	Map->Update();
	hammer->Update();
	for (int i = 0; i < 9; i++)
	{
		moles[i]->Update();
		moleDuration[i] += DELTA;
		if (moleDuration[i] >= 100.0f / (speed * 0.8f))
		{
			moles[i]->visible = false;
		}
	}

	if (time >= 70.0f / speed && od < 120)
	{
		moles[order[od]]->visible = true;
		moleDuration[order[od]] = 0.0f;
		od++;
		speed += 5.0f;

		time = 0.0f;
	}


}

void Main::LateUpdate()
{
	Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
	Vector3 Hit;
	
	if (Map->ComPutePicking(Mouse, Hit))
	{
		Hit.y += 5.0f;
		hammer->SetWorldPos(Hit);
		//cout << Hit.x << " " << Hit.y << " " << Hit.z << endl;
		//   아래-43      위41                   왼 42       오-41
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			if (Hit.x > 41 && Hit.z > 42 && moles[0]->visible)										{ score++; moles[0]->visible = false;}
			if (Hit.x > 41 && Hit.z <= 42 && Hit.z >= -41 && moles[1]->visible)						{ score++; moles[1]->visible = false;}
			if (Hit.x > 41 && Hit.z < -41 && moles[2]->visible)										{ score++; moles[2]->visible = false;}
			if (Hit.x <= 41 && Hit.x >= -43 && Hit.z > 42 && moles[3]->visible)						{ score++; moles[3]->visible = false;}
			if (Hit.x <= 41 && Hit.x >= -43 && Hit.z <= 42 && Hit.z >= -41 && moles[4]->visible)	{ score++; moles[4]->visible = false;}
			if (Hit.x <= 41 && Hit.x >= -43 && Hit.z < -41 && moles[5]->visible)					{ score++; moles[5]->visible = false;}
			if (Hit.x < -43 && Hit.z > 42 && moles[6]->visible)										{ score++; moles[6]->visible = false;}
			if (Hit.x < -43 && Hit.z <= 42 && Hit.z >= -41 && moles[7]->visible)					{ score++; moles[7]->visible = false;}
			if (Hit.x < -43 && Hit.z < -41 && moles[8]->visible)									{ score++; moles[8]->visible = false;}

			hammer->rotation.x = 85 * TORADIAN;
		}
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			hammer->rotation.x = 15 * TORADIAN;
		}
	}
}
void Main::Render()
{
	LIGHT->Set();
	Cam->Set();
	sky->Render();
	Map->Render();
	for (int i = 0; i < 9; i++)
	{
		moles[i]->Render();
	}
	
	hammer->Render();


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
	App.SetAppName(L"MoleGame");
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
