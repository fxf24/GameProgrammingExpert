#include "stdafx.h"

int     LoadingCount = 0;

LoadingScene::LoadingScene()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    Sphere = Actor::Create();
    Sphere->LoadFile("Sphere.xml");
}

LoadingScene::~LoadingScene()
{
    RESOURCE->ReleaseAll();
    Sphere->Release();
    Grid->Release();
    Cam->Release();
  
}





void LoadingScene::Init()
{
    
}

void LoadingScene::Release()
{
   
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

    if (LoadingCount >= LoadingMaxCount)
    {
        t1->join();
        SafeDelete(t1);
        SCENE->ChangeScene(targetName.c_str());
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

void LoadingScene::LoadingTarget(string name, int loadingMaxCount,  void(*FcnPtr)())
{
    t1 = new thread(FcnPtr);
    LoadingCount = 0;
    LoadingMaxCount = loadingMaxCount;
    targetName = name;
}
