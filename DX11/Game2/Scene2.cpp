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
    Map->Release();
    Grid->Release();
}

void Scene2::Init()
{
    time = 0.0f;
    Cam->LoadFile("Cam2.xml");
    Camera::main = Cam;
    ResizeScreen();
}

void Scene2::Release()
{

}


void Scene2::Update()
{
    if (ImGui::Button("ChangeScene"))
    {
        SCENE->ChangeScene("SC1",1.0f)->Init();
        time = 0.0f;
        return;
    }
    if (state == SceneState::FADEIN)
    {
        BLUR->blur._Color.x = 0.5f;
        BLUR->blur._Color.y = 0.5f;
        BLUR->blur._Color.z = 0.5f;
        BLUR->blur._Radius = Util::Lerp(0.0f,2000.0f,time);
        BLUR->blur._Screen = Vector2(App.GetHalfWidth(), App.GetHalfHeight());
        time += DELTA;
        if (time > 1.0f)
        {
            state = SceneState::NONE;
        }
    }
    else if (state == SceneState::FADEOUT)
    {
        time += DELTA;
        BLUR->blur._Radius = Util::Lerp(2000.0f, 0.0f, time);
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
    PostEffect->Update();
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
    BLUR->Set();

    //텍스쳐 위에 그렸던걸 가져와서 매핑
    PostEffect->material->diffuseMap->srv = RT->GetRTVSRV();
    PostEffect->Render();

}

void Scene2::ResizeScreen()
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
