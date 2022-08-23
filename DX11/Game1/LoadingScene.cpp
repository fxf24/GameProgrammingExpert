#include "stdafx.h"
#include "LoadingScene.h"

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
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    sp1 = Actor::Create();
    sp1->LoadFile("Sphere.xml");

    sp2 = Actor::Create();
    sp2->LoadFile("Sphere.xml");
    sp2->scale = Vector3(5, 5, 5);

    Camera::main = Cam;

    lerpValue = 0.0f;
}

void LoadingScene::Release()
{

}


void LoadingScene::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Cam->RenderHierarchy();
    Grid->RenderHierarchy();
    ImGui::End();

    for (int i = 0; i < 4; i++)
    {
        string str = "Point" + to_string(i);
        ImGui::SliderFloat3(str.c_str(), (float*)&Point[i], -100.0f, 100.0);
    }
    lerpValue += DELTA;

    if (lerpValue > 1.0f)
        lerpValue = 0.0f;

    sp1->SetWorldPos(Util::Cubic(Point[0], Point[1], Point[2], Point[3], lerpValue));

    sp1->Update();

    Cam->Update();
    Grid->Update();

}

void LoadingScene::LateUpdate()
{
   
}

void LoadingScene::Render()
{
    sp1->scale.x = LoadingCount * 10.0f;
    sp1->scale.y = LoadingCount * 10.0f;
    sp1->scale.z = LoadingCount * 10.0f;

    Cam->Set();
    Grid->Render();

    for (int i = 0; i < 4; i++)
    {
        sp2->SetWorldPos(Point[i]);
        sp2->Update();
        sp2->Render();
    }

    sp1->Render();
}

void LoadingScene::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}