#include "stdafx.h"
#include "Main.h"

Main::Main()
{
    D3D11_BUFFER_DESC desc = { 0 };
    desc.ByteWidth = sizeof(Brush);
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;
    HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &brushBuffer);
    assert(SUCCEEDED(hr));
    D3D->GetDC()->PSSetConstantBuffers(10, 1, &brushBuffer);
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

    Map = Terrain::Create();
    Map->CreateStructuredBuffer();
    Map->shader = RESOURCE->shaders.Load("5.TerrainEditor.hlsl");

    Sphere = Actor::Create();
    Sphere->LoadFile("Sphere.xml");
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Grid->Release();
    Map->Release();
    Sphere->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::SliderInt("BrushTexture", &brushTexture, 0, 1);
    ImGui::SliderFloat("BrushRange", &brush.range
        , 0.0f, 2000.0f);
    ImGui::InputFloat("BrushHeight", &brushMaxHeight);
    ImGui::InputFloat("BrushAddHeightScalr", &brushAddHeightScalr);
    if (ImGui::Button("Rect"))
    {
        brush.shape = 0;
    }
    ImGui::SameLine();
    if (ImGui::Button("Circle"))
    {
        brush.shape = 1;
    }

    if (ImGui::Button("1"))
    {
        brush.type = 0;
    }
    ImGui::SameLine();
    if (ImGui::Button("2"))
    {
        brush.type = 1;
    }
    ImGui::SameLine();
    if (ImGui::Button("3"))
    {
        brush.type = 2;
    }



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

        int terrainSize = (int)sqrt(Size);
        int triSize = (terrainSize - 1) * (terrainSize - 1) * 2;
        float half = terrainSize * 0.5f;

        VertexTerrain* vertices = new VertexTerrain[Size];
       
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

                vertices[Index].uv = Vector2(_u, _v);
                vertices[Index].position = Vector3(_x, _y, _z);
                vertices[Index].normal = Vector3(0, 1, 0);
            }
        }

        UINT* indices = new UINT[triSize * 3];
        int Idx = 0;
        for (int z = 0; z < terrainSize - 1; z++)
        {
            for (int x = 0; x < terrainSize - 1; x++)
            {
                UINT Index = z * terrainSize + x;
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
        Map->mesh = make_shared<Mesh>(vertices, Size, indices, Idx,
            VertexType::TERRAIN);
        Map->UpdateMeshNormal();

        
            //UINT* indices, UINT indexCount,
            //VertexType type





        //파일 닫기
        fclose(fp);

        //가로 x 세로 값으로 높이값 메쉬를 만들기

    }


    ImGui::End();

    Cam->Update();
    Grid->Update();
    Map->Update();
    Sphere->Update();
}

void Main::LateUpdate()
{
    Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
    Vector3 Hit;
    if (Map->ComPutePicking(Mouse, brush.point))
    {

        if (INPUT->KeyPress(VK_MBUTTON))
        {
            EditTerrain(brush.point);
            Map->DeleteStructuredBuffer();
            Map->CreateStructuredBuffer();
        }
    }
}

void Main::Render()
{
    Cam->Set();
    //Grid->Render();

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    D3D->GetDC()->Map(brushBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy_s(mappedResource.pData, sizeof(Brush), &brush, sizeof(Brush));
    D3D->GetDC()->Unmap(brushBuffer, 0);
    

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

void Main::EditTerrain(Vector3 Pos)
{

    Matrix Inverse = Map->W.Invert();
    Pos = Vector3::Transform(Pos, Inverse);
    float brushRange = brush.range / Map->S._11;

    //정점 갯수만큼
    for (UINT i = 0; i < Map->mesh->vertexCount; i++)
    {
        VertexTerrain* vertices = (VertexTerrain*)Map->mesh->vertices;
        Vector3 v1 = Vector3(Pos.x, 0.0f, Pos.z);
        Vector3 v2 = Vector3(vertices[i].position.x,
            0.0f, vertices[i].position.z);
        Vector3 temp = v2 - v1;
        //두포지션간의 xz 차이의 길이값
        float Dis = temp.Length();
        float w;
        //네모
        if (brush.shape == 0)
        {
            if (fabs(v1.x - v2.x) < brushRange and
                fabs(v1.z - v2.z) < brushRange)
            {                    
                // 0 ~ 1
                w = Dis / brushRange / 1.414f;
                Util::Saturate(w);
                w = 1.0f - w;
                if (brush.type == 0)
                {
                    w = 1.0f;
                }
                else if (brush.type == 1)
                {

                }
                else if (brush.type == 2)
                {
                    w *= PI * 0.5f;
                    w = sinf(w);
                }
            }
            else
            {
                w = 0;
            }
        }
        //원
        else if (brush.shape == 1)
        {
            w = Dis / brushRange;
            Util::Saturate(w);
            w = 1.0f - w;
            if (brush.type == 0)
            {
                if(w > 0.0f)
                w = 1.0f;
            }
            else if (brush.type == 1)
            {

            }
            else if (brush.type == 2)
            {
                w *= PI * 0.5f;
                w = sinf(w);
            }
        }
        vertices[i].position.y
            += w * brushAddHeightScalr * DELTA;

        vertices[i].weights
            += w * ((brushTexture) ? 1 : -1) * DELTA;

        Util::Saturate(vertices[i].weights);

        Util::Saturate(vertices[i].position.y,0.0f ,brushMaxHeight);

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