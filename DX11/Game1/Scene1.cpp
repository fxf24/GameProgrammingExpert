#include "stdafx.h"
#include "Scene1.h"

Scene1::Scene1()
{
    
}

Scene1::~Scene1()
{
}


void Scene1::Init()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    LoadingCount++;
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
    LoadingCount++;

    Map = Actor::Create();
    Map->LoadFile("Terrain.xml");
    LoadingCount++;
    Sphere = Actor::Create();
    Sphere->LoadFile("Sphere.xml");

    cubeMan = new CubeMan();
    cubeMan->anim->PlayAnimation(AnimationState::LOOP, 0);
    LoadingCount++;
    //Cam = (Camera*)cubeMan->Find("Camera");
    Camera::main = Cam;
    cubeManTopRay.direction = Vector3(0, -1, 0);

    lerpValue = 1.0f;
    RlerpValue = 1.0f;
}

void Scene1::Release()
{
    RESOURCE->ReleaseAll();
    Map->Release();
    //MapSurface->Release();
    Grid->Release();
    cubeMan->Release();
}


void Scene1::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Map->RenderHierarchy();
    Cam->RenderHierarchy();
    Grid->RenderHierarchy();
    cubeMan->RenderHierarchy();
    Sphere->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Grid->Update();
    Map->Update();
    //MapSurface->Update();
    cubeMan->Update();
    Sphere->Update();

    if (ImGui::Button("Sc2"))
    {
        SCENE->ChangeScene("LOADING");
    }
}

void Scene1::LateUpdate()
{
    cubeManTopRay.position = cubeMan->GetWorldPos();
    cubeManTopRay.position.y += 1000.0f;
    Vector3 hit;
    if (INPUT->KeyDown(VK_MBUTTON))
    {
        Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
        Vector3 hit;
        if (Util::RayIntersectTriNear(Mouse, Map, hit))
        {
            from = cubeMan->GetWorldPos();
            to = hit;
            lerpValue = 0.0f;
            RlerpValue = 0.0f;

            Vector3 Dir = to - from;
            Dir.y = 0;
            Dir.Normalize();
            //-PI ~ PI
            float Yaw = atan2f(Dir.x, Dir.z);
            //-PI ~ PI
            cubeMan->rotation.y = Util::NormalizeAngle(cubeMan->rotation.y);

            //from cubeMan->rotation.y
            //to Yaw;
            if (fabs(Yaw - cubeMan->rotation.y) > PI)
            {
                if (Yaw > 0)
                {
                    Rfrom = cubeMan->rotation.y + PI_2;
                    Rto = Yaw;
                }
                else
                {
                    Rfrom = cubeMan->rotation.y - PI_2;
                    Rto = Yaw;
                }
            }
            else
            {
                Rfrom = cubeMan->rotation.y;
                Rto = Yaw;
            }


            cubeMan->anim->PlayAnimation(AnimationState::LOOP, 1);
        }
    }

    if (RlerpValue < 1.0f)
    {
        float minus = fabs(Rto - Rfrom);
        RlerpValue += DELTA / minus * PI_2;
        cubeMan->rotation.y = Util::Lerp(Rfrom, Rto, RlerpValue);
        if (RlerpValue > 1.0f)
        {
            cubeMan->rotation.y = Rto;
        }
    }

    if (lerpValue < 1.0f)
    {
        Vector3 coord = Vector3::Lerp(from, to, lerpValue);
        cubeMan->SetWorldPos(coord);
        Vector3 Dis = from - to;
        lerpValue += DELTA / Dis.Length() * 10.0f;

        Vector3 Hit2;
        if (Util::RayIntersectMap(cubeManTopRay, Map, Hit2))
        {
            cubeMan->SetWorldPosY(Hit2.y);
            cout << "¸ÊÀ§¿¡ ÀÖ´Ù" << endl;
        }
        else
        {
            cout << "¸Ê¹Û¿¡ ÀÖ´Ù" << endl;
        }
        if (lerpValue > 1.0f)
        {
            //lerpValue = 0.0f;
            cubeMan->SetWorldPos(to);
            cubeMan->anim->PlayAnimation(AnimationState::LOOP, 0);
        }
    }

    Vector3 P0 = { -50, 0, -50 };
    Vector3 P1 = { -50, 0, 50 };
    Vector3 P2 = { 50, 0, 50 };
    Vector3 P3 = { 50, 0, -50 };

    if (time < 1.0f)
    {
        Vector3 loc = P0 * pow(1 - time, 3) + 3 * P1 * time * pow(1 - time, 2) + 3 * P2 * pow(time, 2) * (1 - time) + P3 * pow(time, 3);
        Sphere->SetWorldPos(loc);

        time += DELTA;
    }
    else
    {
        time = 0.0f;
    }
}

void Scene1::Render()
{
    Cam->Set();
    Grid->Render();
    Map->Render();
    //MapSurface->Render();
    cubeMan->Render();
    Sphere->Render();
}

void Scene1::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}
