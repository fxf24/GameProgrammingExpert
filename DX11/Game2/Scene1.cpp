#include "stdafx.h"

Scene1::Scene1()
{
    sky = Sky::Create();
    Cam = Camera::Create();
    Cam2 = Camera::Create();
    Cam2->LoadFile("Cam3.xml");
  
    Player = Actor::Create();
    Player->LoadFile("Character2.xml");
    Map = Terrain::Create();
    Map->LoadFile("Map2.xml");
    Map->CreateStructuredBuffer();



    RT = new RenderTarget();
}

Scene1::~Scene1()
{
    Map->Release();
}

void Scene1::Init()
{
    
    time = 0.0f;
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    ResizeScreen();
}

void Scene1::Release()
{
   
}


void Scene1::Update()
{
    ImGui::SliderFloat("App.deltaScale", &App.deltaScale, 0.01, 10);


    if (ImGui::Button("1"))
    {
        PostQuitMessage(0);
        return;
    }
    if (ImGui::Button("ChangeScene"))
    {
        SCENE->ChangeScene("SC2", 1.0f)->Init();
        time = 0.0f;
        return;
    }
    if (state == SceneState::FADEIN)
    {
        BLUR->blur._Radius = 2000.0f;
        BLUR->blur._Color
            = Util::Lerp(Vector3(0, 0, 0), Vector3(0.5f, 0.5f, 0.5f), time);
        time += DELTA;
        if (time > 1.0f)
        {
            state = SceneState::NONE;
        }
    }
    else if (state == SceneState::FADEOUT)
    {
        time += DELTA;
        BLUR->blur._Color
            = Util::Lerp(Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 0, 0), time);
    }

    BLUR->Update();






    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    Camera::ControlMainCam();
    LIGHT->RenderDetail();
    //
    ////Ui->RenderHierarchy();
    //
    ImGui::Begin("Hierarchy");
    sky->RenderHierarchy();
    Player->RenderHierarchy();
    Map->RenderHierarchy();
    Cam->RenderHierarchy();
    Cam2->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Cam2->Update();
    Player->Update();
    Map->Update();
    sky->Update();
}

void Scene1::LateUpdate()
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

void Scene1::PreRender()
{
    //atan2(1, 1);
    //환경맵 그리기
    LIGHT->Set();
    Cam2->Set();
    RT->Set();
    Player->Render();

}

void Scene1::Render()
{
    LIGHT->Set();
    Cam->Set();
    Cam2->SetShadow();
    srv = RT->GetDSVSRV();
    D3D->GetDC()->PSSetShaderResources(7, 1, &srv);

    sky->Render();
    Map->Render();
    Player->Render();
}

void Scene1::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();

    Cam2->width = App.GetWidth();
    Cam2->height = App.GetHeight();
    Cam2->viewport.width = App.GetWidth();
    Cam2->viewport.height = App.GetHeight();



    if (RT)
    {
        RT->ResizeScreen(Cam2->viewport.width, Cam2->viewport.height);
    }
}
