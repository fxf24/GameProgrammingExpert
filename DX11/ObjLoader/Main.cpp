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
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Grid->Release();

}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Grid->RenderHierarchy();
    Cam->RenderHierarchy();
    for (size_t i = 0; i < List.size(); i++)
    {
        List[i]->RenderHierarchy();
    }

    ImGui::End();

    ImGui::Begin("ObjLoader");

    if (GUI->FileImGui("Load", "Load Obj",
        ".obj", "../Obj"))
    {
        string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
        
        string file = "../Obj/" + path;
        //파일 열기
        ifstream fin;
        fin.open(file, ios::in);
        if (!fin.is_open()) return;

        vector<VertexPCN> v;
        vector<Vector3> position;
        vector<Vector3> normal;

        vector<UINT> vecindices;

        while (!fin.eof())
        {
            string Input;
            fin >> Input;

            if (Input[0] != 'v' && Input[0] != 'f')
            {
                char c[128];
                fin.getline(c, 128);
            }
            else
            {
                if (Input[0] == 'v')
                {
                    if (Input[1] == 't')
                    {

                    }
                    else if (Input[1] == 'n')
                    {
                        Vector3 no;
                        fin >> no.x >> no.y >> no.z;
                        normal.push_back(no);
                    }
                    else
                    {
                        Vector3 pos;
                        fin >> pos.x >> pos.y >> pos.z;
                        position.push_back(pos);
                    }
                }
                //f일때 ex) 1/10/1 posision/uv/normal index number
                else 
                {
                    string index;
                    for (int i = 0; i < 3; i++)
                    {
                        fin >> index;
                        vecindices.push_back(index[0]-'0' -1);
                    }
                }
            }
        }

        for (int i = 0; i < position.size(); i++)
        {
            v.push_back(VertexPCN(position[i], Color(0.5f, 0.5f, 0.5f), normal[i]));
        }

        int vertexCount = v.size();
        int indexCount = vecindices.size();

        VertexPCN* Vertex = new VertexPCN[vertexCount];
        copy(v.begin(), v.end(), stdext::checked_array_iterator<VertexPCN*>(Vertex, vertexCount));

        UINT* indices = new UINT[indexCount];
        copy(vecindices.begin(), vecindices.end(), stdext::checked_array_iterator<UINT*>(indices, indexCount));

        void* vertices = (void*)Vertex;
        Actor* temp = Actor::Create(path);
        Mesh* mesh = new Mesh(vertices, (UINT)vertexCount, indices, (UINT)indexCount, VertexType::PCN);
        mesh->file = "2." + path + ".mesh";
        mesh->SaveFile(mesh->file);
        temp->mesh = RESOURCE->meshes.Load("2." + path + ".mesh");
        temp->shader = RESOURCE->shaders.Load("2.Cube.hlsl");
        List.push_back(temp);

        /*SafeReset(mesh);
        mesh = RESOURCE->meshes.Load(path);*/
    }

    ImGui::End();

    Cam->Update();
    Grid->Update();
    for (size_t i = 0; i < List.size(); i++)
    {
        List[i]->Update();
    }
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    Cam->Set();
    Grid->Render();
    for (size_t i = 0; i < List.size(); i++)
    {
        List[i]->Render();
    }
}

void Main::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"Game1");
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