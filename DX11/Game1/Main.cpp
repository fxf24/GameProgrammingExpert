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
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
    Map = Actor::Create();
    Map->LoadFile("Map.xml");
    MapSurface = Actor::Create();
    MapSurface->LoadFile("MapSurface.xml");

    cubeMan = new CubeMan();
    //Cam = (Camera*)cubeMan->Find("Camera");
    Camera::main = Cam;
    cubeManTopRay.direction = Vector3(0, -1, 0);
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Map->Release();
    MapSurface->Release();
    Grid->Release();
    cubeMan->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d",TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Map->RenderHierarchy();
    MapSurface->RenderHierarchy();
    Grid->RenderHierarchy();
    cubeMan->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Grid->Update();
    Map->Update();
    MapSurface->Update();
    cubeMan->Update();
}

void Main::LateUpdate()
{
    cubeManTopRay.position = cubeMan->GetWorldPos();
    cubeManTopRay.position.y += 1000.0f;
    Vector3 hit;
    if (Util::RayIntersectTri(cubeManTopRay, MapSurface->Find("Rectangle19"), hit))
    {
        float LastFoot = cubeMan->GetLastPos().y - 10.0f;

        //내려가야함
        if (LastFoot > hit.y)
        {
            cubeMan->Falling();
            cubeMan->WorldUpdate();
        }
        else if (LastFoot < hit.y)
        {
            cubeMan->Landing();

            if(hit.y - LastFoot < 3.0f)
                cubeMan->SetWorldPosY(hit.y + 10.0f);
               
            else
            {
                cubeMan->SetWorldPosX(cubeMan->GetLastPos().x);
                cubeMan->SetWorldPosZ(cubeMan->GetLastPos().z);
            }
            cubeMan->WorldUpdate();
        }
        
    }
    //맵 밖
    else
    {
        cubeMan->SetWorldPos(cubeMan->GetLastPos());
        cubeMan->WorldUpdate();
    }

    /*if (Map->Find("Box04")->collider->Intersect(cubeMan->collider))
    {
        cout << "충돌" << endl;
    }*/
}

void Main::Render()
{
    Cam->Set();
    Grid->Render();
    Map->Render();
    MapSurface->Render();
    cubeMan->Render();
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
	App.SetAppName(L"Game1");
	App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
	Main * main = new Main();
    main->Init();
	int wParam = (int)WIN->Run(main);
    main->Release();
	SafeDelete(main);
    D3D->DeleteSingleton();
	WIN->DeleteSingleton();

	return wParam;
}