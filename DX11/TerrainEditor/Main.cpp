#include "stdafx.h"
#include "Main.h"

Main::Main()
{

}

Main::~Main()
{

}

void Main::Init()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    Map = Actor::Create();
    Map->shader = RESOURCE->shaders.Load("3.Cube.hlsl");
    Map->material = make_shared<Material>();

    Sphere = Actor::Create();
    Sphere->LoadFile("Sphere.xml");
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Grid->Release();
}


void Main::Update()
{
    Camera::ControlMainCam(100.0f);

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Grid->RenderHierarchy();
    Map->RenderHierarchy();

    ImGui::End();

    ImGui::Begin("LoadRawFile");

    if (GUI->FileImGui("Load", "LoadRawFile",
        ".raw,.RAW", "../Contents/Raw"))
    {
        string path = ImGuiFileDialog::Instance()->GetCurrentPath();
        Util::Replace(&path, "\\", "/");
        if (path.find("/Raw/") != -1)
        {
            size_t tok = path.find("/Raw/") + 5;
            path = path.substr(tok, path.length())
                + "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
        }
        else
        {
            path = ImGuiFileDialog::Instance()->GetCurrentFileName();
        }
        string file = "../Contents/Raw/" + path;
        FILE* fp;
        //파일 열기
        fopen_s(&fp, file.c_str(), "rb");
        fseek(fp, 0, SEEK_END);
        int Size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        BYTE* Height = new BYTE[Size];

        for (int i = 0; i < Size; i++)
        {
            char c = fgetc(fp);
            Height[i] = c;
            //cout << (int)Height[i] << endl;
        }

        //파일 닫기
        fclose(fp);

        //가로 x 세로 값으로 높이값 메쉬를 만들기
        int terrainSize = (int)sqrt(Size);
        int triSize = (terrainSize - 1) * (terrainSize - 1) * 2;
        float half = terrainSize * 0.5f;
        
        VertexPTN* Vertices = new VertexPTN[Size];
        for (int z = 0; z < terrainSize; z++)
        {
            for (int x = 0; x < terrainSize; x++)
            {
                int Index = (z * terrainSize) + x;
                float _x = x - half;
                float _z = -z + half;
                float _y = Height[Index]/255.0f * (float)terrainSize;

                float _u = float(x) / float(terrainSize - 1);
                float _v = float(z) / float(terrainSize - 1);

                Vertices[Index].uv = Vector2(_u, _v);
                Vertices[Index].position = Vector3(_x, _y, _z);
                Vertices[Index].normal = Vector3(0, 1, 0);

            }
        }
        
        UINT* indices = new UINT[triSize * 3];
        int Idx = 0;
        for (int z = 0; z < terrainSize - 1; z++)
        {
            for (int x = 0; x < terrainSize - 1; x++)
            {
                int Index = (z * terrainSize) + x;
                indices[Idx] = Index;
                Idx++;
                indices[Idx] = Index + 1;
                Idx++;
                indices[Idx] = Index + terrainSize + 1;
                Idx++;
                indices[Idx] = Index;
                Idx++;
                indices[Idx] = Index + terrainSize + 1;
                Idx++;
                indices[Idx] = Index + terrainSize;
                Idx++;
            }
        }
        Map->mesh = make_shared<Mesh>(Vertices, Size, indices, Idx, VertexType::PTN);
        UpdateTerrainNormal();
    }


    ImGui::End();

    Cam->Update();
    Grid->Update();
    Map->Update();
    Sphere->Update();

}

void Main::LateUpdate()
{
    if (INPUT->KeyDown(VK_LBUTTON))
    {
        Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
        Vector3 hit;
        if (Util::RayIntersectTriNear(Mouse, Map, hit))
        {
            Sphere->SetWorldPos(hit);
        }
    }
}

void Main::Render()
{
    Cam->Set();
    Grid->Render();
    Map->Render();
    Sphere->Render();
}

void Main::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}

void Main::UpdateTerrainNormal()
{
    VertexPTN* vertices = (VertexPTN*)Map->mesh->vertices;
    vector<Vector3> Normals;
    Normals.resize(Map->mesh->vertexCount);

    for (UINT i = 0; i < Map->mesh->indexCount / 3; i++)
    {
        UINT index0 = Map->mesh->indices[i * 3 + 0];
        UINT index1 = Map->mesh->indices[i * 3 + 1];
        UINT index2 = Map->mesh->indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].position;
        Vector3 v1 = vertices[index1].position;
        Vector3 v2 = vertices[index2].position;

        Vector3 A = v1 - v0;
        Vector3 B = v2 - v0;

        Vector3 normal = A.Cross(B);
        normal.Normalize();

        Normals[index0] += normal;
        Normals[index1] += normal;
        Normals[index2] += normal;
    }

    for (UINT i = 0; i < Map->mesh->vertexCount; i++)
    {
        Normals[i].Normalize();
        vertices[i].normal = Normals[i];
    }
    Map->mesh->UpdateMesh();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"TerrainEditor");
    App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
    Main* main = new Main();
    main->Init();
    int wParam = (int)WIN->Run(main);
    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}