#include "stdafx.h"

Scene2::Scene2()
{
    sky = Sky::Create();

    Cam = Camera::Create();

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    Player = Actor::Create();
    Player->LoadFile("Character2.xml");

    Map = Terrain::Create();
    Map->LoadFile("Map2.xml");
    Map->CreateStructuredBuffer();

    Point = Light::Create("L1");
    Point2 = Light::Create("L2");

    RT = new RenderTarget();

    PostEffect = UI::Create();
    PostEffect->LoadFile("Window2.xml");
}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
    time = 0.0f;
    ResizeScreen();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
}

void Scene2::Release()
{
    RESOURCE->ReleaseAll();
}


void Scene2::Update()
{
    if (ImGui::Button("ChangeScene"))
    {
        SCENE->ChangeScene("SC1", 1.0f)->Init();
        time = 0.0f;
        return;
    }

    if (state == SceneState::FADEIN)
    {
        BLUR->blur.blendColor.x = 0.5f;
        BLUR->blur.blendColor.y = 0.5f;
        BLUR->blur.blendColor.z = 0.5f;
        BLUR->blur.radius = Util::Lerp(0.0f, 2000.0f, time);
        time += DELTA;
        if (time > 1.0f)
        {
            state = SceneState::NONE;
        }
    }
    else if (state == SceneState::FADEOUT)
    {
        time += DELTA;
        BLUR->blur.radius = Util::Lerp(2000.0f, 0.0f, time);
    }

    BLUR->Update();

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

}

void Scene2::LateUpdate()
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

void Scene2::PreRender()
{
    RT->Set();
    LIGHT->Set();
    Cam->Set();
    sky->Render();
    Point->Render();
    Point2->Render();
    Grid->Render();

    Player->Render();
    Map->Render();
}

void Scene2::Render()
{


    PostEffect->material->diffuseMap->srv
        = RT->GetRTVSRV();
    PostEffect->Update();
    PostEffect->Render();
}

void Scene2::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}