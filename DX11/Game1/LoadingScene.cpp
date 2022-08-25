#include "stdafx.h"
#include "Main.h"
void LoadingScene1()
{
    SCENE->AddScene("SC1", new Scene1());
}

int     LoadingCount = 0;

LoadingScene::LoadingScene()
{
    
}

LoadingScene::~LoadingScene()
{
    
}





void LoadingScene::Init()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    Sphere = Actor::Create();
    Sphere->LoadFile("Sphere.xml");

    t1 = new thread(LoadingScene1);
}

void LoadingScene::Release()
{
    Sphere->Release();
    Grid->Release();
    Cam->Release();
    t1->join();
    SafeDelete(t1);
    RESOURCE->ReleaseAll();
}


void LoadingScene::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Sphere->RenderHierarchy();
    Grid->RenderHierarchy();
    Cam->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Grid->Update();
    Sphere->Update();

    if (LoadingCount >= 4)
    {
        LoadingCount = 0;
        SCENE->ChangeScene("SC1");
    }
}

void LoadingScene::LateUpdate()
{
   
}

void LoadingScene::Render()
{
    Sphere->scale.x = LoadingCount * 10.0f;
    Sphere->scale.y = LoadingCount * 10.0f;
    Sphere->scale.z = LoadingCount * 10.0f;

    Cam->Set();
    Grid->Render();
    Sphere->Render();
}

void LoadingScene::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}