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

    Point = Actor::Create();
    Point->LoadFile("Sphere.xml");

    Point2 = Light::Create("L2");



    RT = new RenderTarget();
    PostEffect = UI::Create();
    PostEffect->LoadFile("Window2.xml");

    cubeMap = new CubeMap(1000,1000);
    sphere = Actor::Create();
    sphere->LoadFile("Sphere2.xml");
    /*sphere->material = make_shared<Material>();
    sphere->material->environmentMap = make_shared<Texture>();
    sphere->material->environment = 1.0f;*/
    cubeMappingShader = new Shader();
    cubeMappingShader->LoadFile("0.ExamCubeMap.hlsl");
    cubeMappingShader->LoadGeometry();

    cubeMappingShader2 = new Shader();
    cubeMappingShader2->LoadFile("4.CubeMap.hlsl");
    cubeMappingShader2->LoadGeometry();

    cubeMappingShader3 = new Shader();
    cubeMappingShader3->LoadFile("5.CubeMap.hlsl");
    cubeMappingShader3->LoadGeometry();

    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(Refraction);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &refractionBuffer);
        assert(SUCCEEDED(hr));

    }
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
    ImGui::SliderFloat("refractionIdx", &refractionIdx, 0, 2.0f);

    desc.RefractionIdx = refractionIdx;
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        D3D->GetDC()->Map(refractionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        memcpy_s(mappedResource.pData, sizeof(Refraction), &desc, sizeof(Refraction));
        D3D->GetDC()->Unmap(refractionBuffer, 0);
        D3D->GetDC()->PSSetConstantBuffers(4, 1, &refractionBuffer);
    }
    
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
    //반사
    /*Vector3 Dir = sphere->GetWorldPos() - Camera::main->GetWorldPos();
    float dis = Dir.Length();
    Dir.Normalize();
    Vector3 reflect = Vector3::Reflect(Dir, sphere->GetUp());
    Vector3 Pos = sphere->GetWorldPos() - reflect * dis;
    Point->SetWorldPos(Pos);*/

    //굴절
    Vector3 Dir2 = sphere->GetWorldPos() - Camera::main->GetWorldPos();
    float dis2 = Dir2.Length();
    Dir2.Normalize();
    Vector3 refract = Vector3::Refract(Dir2, sphere->GetUp(), refractionIdx);
    Vector3 Pos2 = sphere->GetWorldPos() - refract * dis2;
    Point->SetWorldPos(Pos2);

    //atan2(1, 1);
    //환경맵 그리기
    LIGHT->Set();
    cubeMap->Set(Pos2);
    //cubeMap->Set(sphere->GetWorldPos());
    sky->Render(cubeMappingShader);
    Map->Render(cubeMappingShader3);
    Player->Render(cubeMappingShader2);


    //포스트이펙트 텍스쳐에 그리기
    RT->Set();
    Cam->Set();
    sky->Render();
    Point->Render();
    Point2->Render();
    Grid->Render();
    Player->Render();
    Map->Render();
    sphere->material->environmentMap = cubeMap->GetRTVSRV();
    BLEND->Set(true);
    sphere->Render();
    BLEND->Set(false);
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
