#include "stdafx.h"

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

    Map = Terrain::Create();
    Map->LoadFile("Terrain.xml");
    Map->CreateStructuredBuffer();
    LoadingCount++;

    cubeMan = new CubeMan();
    LoadingCount++;
    Camera::main = Cam;
    cubeManTopRay.direction = Vector3(0, -1, 0);

    lerpValue = 1.0f;
    RlerpValue = 1.0f;
}

void Scene1::Release()
{
    RESOURCE->ReleaseAll();
    Map->Release();
    Grid->Release();
    cubeMan->Release();
}


void Scene1::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Map->RenderHierarchy();
    Grid->RenderHierarchy();
    cubeMan->RenderHierarchy();
    Cam->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Grid->Update();
    Map->Update();
    cubeMan->Update();

    if (ImGui::Button("Sc2"))
    {
        SCENE->ChangeScene("LOADING");
        reinterpret_cast<LoadingScene*>(SCENE->GetScene("LOADING"))
            ->LoadingTarget("SC2", 4,
                []()
        { SCENE->GetScene("SC2")->Init(); }
        );
        return;
    }
}

void Scene1::LateUpdate()
{
    cubeManTopRay.position = cubeMan->GetWorldPos();
    cubeManTopRay.position.y += 1000.0f;
    Vector3 hit;

    if (INPUT->KeyDown(VK_F1))
    {
        Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
        Vector3 Hit, Hit2;
        Ray CharacterToMouse;
        Map->ComPutePicking(Mouse, Hit);

        CharacterToMouse.position = cubeMan->GetWorldPos();
        CharacterToMouse.direction = Hit - cubeMan->GetWorldPos();
        CharacterToMouse.direction.Normalize();

        if (Map->RayCastingCollider(CharacterToMouse, Hit2))
        {
            cout << "콜라이더에 막힘" << endl;
            path.clear();
            path.push_back(cubeMan->GetWorldPos());
            deque<Vector3> way;
            Map->PathFinding(way, Map->PickNode(cubeMan->GetWorldPos()), Map->PickNode(Hit));
            reverse(way.begin(), way.end());
            path.insert(path.end(), way.begin(), way.end());
            path.push_back(Hit);

            findPath = true;
            route = 0;
        }
        else
        {
            from = cubeMan->GetWorldPos();
            //from.y = 0.0f;
            to = Hit;
            //to.y = 0.0f;
            lerpValue = 0.0f;

            Vector3 Dir = Hit - cubeMan->GetWorldPos();
            Dir.y = 0;
            Dir.Normalize();
            // -PI ~ PI
            float Yaw = atan2f(Dir.x, Dir.z);
            // -PI ~ PI
            cubeMan->rotation.y = Util::NormalizeAngle(cubeMan->rotation.y);

            //to Yaw;
            if (fabs(Yaw - cubeMan->rotation.y) > PI)
            {
                if (Yaw > 0)
                {
                    Rfrom = cubeMan->rotation.y + PI * 2.0f;
                    Rto = Yaw;
                }
                else
                {
                    Rfrom = cubeMan->rotation.y - PI * 2.0f;
                    Rto = Yaw;
                }
            }
            else
            {
                Rfrom = cubeMan->rotation.y;
                Rto = Yaw;
            }
            RlerpValue = 0.0f;
        }
    }

    if (INPUT->KeyDown(VK_MBUTTON))
    {
        Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
        Vector3 Hit;
        if (Map->ComPutePicking(Mouse, Hit))
        {
            //cubeMan->SetWorldPos(Hit);
            from = cubeMan->GetWorldPos();
            //from.y = 0.0f;
            to = Hit;
            //to.y = 0.0f;
            lerpValue = 0.0f;

            Vector3 Dir = Hit - cubeMan->GetWorldPos();
            Dir.y = 0;
            Dir.Normalize();
            // -PI ~ PI
            float Yaw = atan2f(Dir.x, Dir.z);
            // -PI ~ PI
            cubeMan->rotation.y = Util::NormalizeAngle(cubeMan->rotation.y);

            //to Yaw;
            if (fabs(Yaw - cubeMan->rotation.y) > PI)
            {
                if (Yaw > 0)
                {
                    Rfrom = cubeMan->rotation.y + PI * 2.0f;
                    Rto = Yaw;
                }
                else
                {
                    Rfrom = cubeMan->rotation.y - PI * 2.0f;
                    Rto = Yaw;
                }
            }
            else
            {
                Rfrom = cubeMan->rotation.y;
                Rto = Yaw;
            }
            RlerpValue = 0.0f;
            //cubeMan->rotation.y = Yaw;
        }
    }

    if (findPath)
    {
        from = path[route];
        //from.y = 0.0f;
        to = path[route + 1];
        //to.y = 0.0f;
        lerpValue = 0.0f;

        Vector3 Dir = path[route + 1] - path[route];
        Dir.y = 0;
        Dir.Normalize();
        // -PI ~ PI
        float Yaw = atan2f(Dir.x, Dir.z);
        // -PI ~ PI
        cubeMan->rotation.y = Util::NormalizeAngle(cubeMan->rotation.y);

        //to Yaw;
        if (fabs(Yaw - cubeMan->rotation.y) > PI)
        {
            if (Yaw > 0)
            {
                Rfrom = cubeMan->rotation.y + PI * 2.0f;
                Rto = Yaw;
            }
            else
            {
                Rfrom = cubeMan->rotation.y - PI * 2.0f;
                Rto = Yaw;
            }
        }
        else
        {
            Rfrom = cubeMan->rotation.y;
            Rto = Yaw;
        }
        RlerpValue = 0.0f;
        findPath = false;
    }


    if (RlerpValue < 1.0f)
    {
        float minus = fabs(Rto - Rfrom);

        RlerpValue += DELTA / minus * PI * 2.0f;
        cubeMan->rotation.y = Util::Lerp(Rfrom, Rto, RlerpValue);
        if (RlerpValue > 1.0f)
        {
            cubeMan->rotation.y = Rto;
        }
    }


    if (lerpValue < 1.0f)
    {
        Vector3 coord = Util::Lerp(from, to, lerpValue);
        cubeMan->SetWorldPos(coord);
        Vector3 Dis = from - to;
        lerpValue += DELTA / Dis.Length() * 100.0f;

        Vector3 Hit2;
        if (Util::RayIntersectMap(cubeManTopRay, Map, Hit2))
        {
            cubeMan->SetWorldPosY(Hit2.y);
            //cout << "맵위에있다" << endl;
        }
        else
        {
            cout << "맵밖에있다" << endl;
        }

        if (lerpValue > 1.0f)
        {
            //lerpValue = 0.0f;
            cubeMan->SetWorldPos(to);

            if (route < path.size() - 2)
            {
                route++;
                findPath = true;
            }
        }
    }
}

void Scene1::Render()
{
    Cam->Set();
    Grid->Render();
    Map->Render();

    cubeMan->Render();
}

void Scene1::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}