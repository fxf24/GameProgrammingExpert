#include "stdafx.h"

Scene1::Scene1()
{
    sky = Sky::Create();
    Cam = Camera::Create();
  
    Player = Actor::Create();
    Player->LoadFile("Character2.xml");
    Map = Terrain::Create();
    Map->LoadFile("Map2.xml");
    Map->CreateStructuredBuffer();
    Map->material->shadow = 1.0f;
    //Player->Find("Vampire")->material->shadow = 1.0f;
    //Player->Find("VampireMeshObject")->material->shadow = 1.0f;

   


    cube1 = Actor::Create();
    cube1->LoadFile("Sphere2.xml");
    cube2 = Actor::Create();
    cube2->LoadFile("Sphere3.xml");

    shadow = new Shadow();
    cubeMap1 = new Environment(512, 512);
    cubeMap2 = new Environment(512, 512);
    cubeMap1->desc2.CubeMapType = 0;
    cubeMap2->desc2.CubeMapType = 2;
    postEffect = new PostEffect();
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
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    Camera::ControlMainCam();
    LIGHT->RenderDetail();
    shadow->RenderDetail();
    //cubeMap1->RenderDetail();
    //cubeMap2->RenderDetail();
    postEffect->RenderDetail();


    ImGui::Begin("Hierarchy");
    sky->RenderHierarchy();
    Player->RenderHierarchy();
    Map->RenderHierarchy();
    Cam->RenderHierarchy();
    cube1->RenderHierarchy();
    cube2->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Player->Update();
    Map->Update();
    sky->Update();
    cube1->Update();
    cube2->Update();
}

void Scene1::LateUpdate()
{
    Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
    Vector3 Hit;
    if (Map->ComPutePicking(Mouse, Hit))
    {
        Player->SetWorldPos(Hit);
        cout << endl;
    }
}

void Scene1::PreRender()
{
    LIGHT->Set();
    //환경 매핑 그리기
    {
        Vector3 Dir = cube1->GetWorldPos() - Camera::main->GetWorldPos();
        float Distance = Dir.Length();
        Dir.Normalize();
        Vector3 reflect = Vector3::Reflect(Dir, cube1->GetUp());
        cubeMap1->SetCapture(cube1->GetWorldPos() - reflect * Distance);
        sky->CubeMapRender();
        Player->CubeMapRender();
        Map->CubeMapRender();
    }
    //환경 매핑 그리기
    {
        cubeMap2->SetCapture(Camera::main->GetWorldPos());
        sky->CubeMapRender();
        Player->CubeMapRender();
        Map->CubeMapRender();
    }
    //그림자 텍스쳐 그리기
    {
        //shadow->SetCapture(Player->GetWorldPos());
        shadow->SetCapture(Vector3(0,0,0));
        Map->ShadowMapRender();
        Player->ShadowMapRender();
        cube1->ShadowMapRender();
        cube2->ShadowMapRender();
    }
    //포스트이펙트 텍스쳐에 그리기
    {
        postEffect->SetCapture();
        Cam->Set();
        sky->Render();

        cubeMap1->SetTexture();
        cube1->Render();

        cubeMap2->SetTexture();
        cube2->Render();

        shadow->SetTexture();
        Map->Render();
        Player->Render();

    }
    
}

void Scene1::Render()
{
    postEffect->Render();
}

void Scene1::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();

    if (postEffect)
    {
        postEffect->ResizeScreen(App.GetWidth(), App.GetHeight());
    }
}
