#include "stdafx.h"

Scene1::Scene1()
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

    cubeMap = new CubeMap();
    sphere = Actor::Create();
    sphere->LoadFile("Sphere2.xml");
    sphere->material = make_shared<Material>();
    sphere->material->environmentMap = make_shared<Texture>();
    sphere->material->environment = 1.0f;
    cubeMappingShader = new Shader();
    cubeMappingShader->LoadFile("0.ExamCubeMap.hlsl");
    cubeMappingShader->LoadGeometry();

    cubeMappingShader2 = new Shader();
    cubeMappingShader2->LoadFile("4.CubeMap.hlsl");
    cubeMappingShader2->LoadGeometry();
}

Scene1::~Scene1()
{
    Map->Release();
    Grid->Release();
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
    if (ImGui::Button("ChangeScene"))
    {
        SCENE->ChangeScene("SC2", 1.0f)->Init();
        time = 0.0f;
        return;
    }
    if (state == SceneState::FADEIN)
    {
        BLUR->blur.radius = 2000.0f;
        BLUR->blur.blendColor
            = Color::Lerp(Color(0, 0, 0), Color(0.5f, 0.5f, 0.5f), time);
        time += DELTA;
        if (time > 1.0f)
        {
            state = SceneState::NONE;
        }
    }
    else if (state == SceneState::FADEOUT)
    {
        time += DELTA;
        BLUR->blur.blendColor
            = Color::Lerp(Color(0.5f, 0.5f, 0.5f), Color(0, 0, 0), time);
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
    sphere->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Grid->Update();
    Player->Update();
    Map->Update();
    Point->Update();
    sphere->Update();
    Point2->Update();
    sky->Update();
    PostEffect->Update();
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
    //환경맵 그리기
    LIGHT->Set();
    cubeMap->Set(sphere->GetWorldPos());
    sky->Render(cubeMappingShader2);


    //포스트이펙트 텍스쳐에 그리기
    RT->Set();
    Cam->Set();
    sky->Render();
    Point->Render();
    Point2->Render();
    Grid->Render();
    Player->Render();
    Map->Render();
    sphere->material->environmentMap->srv = cubeMap->GetRTVSRV();
   
    sphere->Render();
}

void Scene1::Render()
{
    //포스트이펙트 렌더
    BLUR->Set();
    PostEffect->material->diffuseMap->srv = RT->GetRTVSRV();
    PostEffect->Render();
}

void Scene1::ResizeScreen()
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
