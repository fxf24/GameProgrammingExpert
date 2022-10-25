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
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	Player = Actor::Create();
	Player->LoadFile("Character2.xml");

	Map = Terrain::Create();
	//Map->LoadFile("Map.xml");
	Map->LoadFile("Map2.xml");
	Map->CreateStructuredBuffer();

	Point = Light::Create("L1");
	Point2 = Light::Create("L2");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Sphere[i][j] = Actor::Create();
			Sphere[i][j]->LoadFile("Sphere.xml");
			Sphere[i][j]->SetWorldPos(Vector3(-85.0f + i * 85.0f, 0.0f,
				85.0f - j * 85.0f));
		}
	}


	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();

	//뷰포트 크기와 렌더타겟 크기를 맞춰야한다.
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();

	RT = new RenderTarget();

	PostEffect = UI::Create();
	PostEffect->LoadFile("Window2.xml");

	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(Blur);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &blurBuffer);
		D3D->GetDC()->PSSetConstantBuffers(10, 1, &blurBuffer);
		assert(SUCCEEDED(hr));
	}

}


void Main::Release()
{

}

void Main::Update()
{
	ImGui::SliderInt("Select", &blur.select, 0, 7);
	ImGui::SliderInt("Count", &blur.count, 0, 200);
	ImGui::SliderFloat("Width", &blur.width, 0, App.GetWidth());
	ImGui::SliderFloat("Height", &blur.height, 0, App.GetHeight());
	ImGui::ColorEdit3("BlendColor", (float*)&blur.blendColor);
	ImGui::SliderFloat2("Center", (float*)&blur.center,0,2000.0f);
	ImGui::SliderFloat("Radius", (float*)&blur.radius,0,2000.0f);
	if (ImGui::Button("ChangeScene"))
	{
		if (changeScene)
		{
			changeScene = !changeScene;
			action = true;
		}
		else
		{
			changeScene = !changeScene;
			action = false;
		}
	}

	if (changeScene)
	{
		if (blur.radius < 300.f && action)
		{
			blur.radius += 150.0f * DELTA;
		}
		else if (!action)
		{
			blur.blendColor -= Color(0.25f * DELTA, 0.25f * DELTA, 0.25f * DELTA, 0.25f * DELTA);

			if (blur.blendColor.R() <= 0.0f)
			{
				action = true;
				blur.blendColor = Color(0.5f, 0.5f, 0.5f, 1.0f);
				blur.radius = 0.0f;
			}
		}
	}
	else
	{
		if (blur.radius > 0.0f && action)
		{
			blur.radius -= 150.0f * DELTA;	
		}
		else if (action)
		{
			action = false;
			blur.radius = 2000.0f;
			blur.blendColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			if (blur.blendColor.R() > 0.5f)
				blur.blendColor -= Color(0.25f * DELTA, 0.25f * DELTA, 0.25f * DELTA, 0.25f * DELTA);
		}
	}

	



	// World
	Vector4 Top;
	Top.x = Player->GetWorldPos().x;
	Top.y = Player->GetWorldPos().y;
	Top.z = Player->GetWorldPos().z;
	Top.w = 1.0f;

	// View
	Top = Vector4::Transform(Top, Cam->view);
	Top = Vector4::Transform(Top, Cam->proj);

	//NDC
	Top.x /= Top.w;
	Top.y /= Top.w;

	//Screen
	Top.x = (Top.x + 1.0f) * App.GetHalfWidth();
	Top.y = (-Top.y + 1.0f) * App.GetHalfHeight();

	blur.center.x = Top.x;
	blur.center.y = Top.y;
	Pos.x = (Player->GetWorldPos().x + 128.0f) / (256.0f / 3.0f);
	Pos.y = (Player->GetWorldPos().z - 128.0f) / (-256.0f / 3.0f);

	ImGui::Text("X: %d  Y: %d ", Pos.x, Pos.y);

	


	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	Camera::ControlMainCam();
	LIGHT->RenderDetail();
	//
	////Ui->RenderHierarchy();
	//
	ImGui::Begin("Hierarchy");
	Point->RenderHierarchy();
	Point2->RenderHierarchy();
	sky->RenderHierarchy();
	Player->RenderHierarchy();
	Map->RenderHierarchy();
	Cam->RenderHierarchy();
	ImGui::End();


	Cam->Update();
	Grid->Update();
	Player->Update();
	Map->Update();
	Point->Update();
	Point2->Update();
	sky->Update();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Sphere[i][j]->Update();

		}
	}
}

void Main::LateUpdate()
{
	Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
	Vector3 Hit;
	//if (Map->ComPutePicking(Mouse, Hit))
	if (Map->ComPutePicking(Mouse, Hit))
	{
		Player->SetWorldPos(Hit);
		cout << endl;
	}


}
void Main::PreRender()
{
	RT->Set();
	LIGHT->Set();
	Cam->Set();
	sky->Render();
	Point->Render();
	Point2->Render();
	Grid->Render();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Sphere[i][j]->Render();

		}
	}
	Player->Render();
	Map->Render();
}
void Main::Render()
{

	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(blurBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Blur) , &blur, sizeof(Blur));
		D3D->GetDC()->Unmap(blurBuffer, 0);
	}


	PostEffect->material->diffuseMap->srv
		= RT->GetRTVSRV();
	PostEffect->Update();
	PostEffect->Render();

}

void Main::ResizeScreen()
{
	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();

	if (RT)
	{
		RT->ResizeScreen(Cam->viewport.width, Cam->viewport.height);
	}
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
