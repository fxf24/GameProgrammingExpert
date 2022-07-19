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
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Cam->Release();
    Grid->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Cam->RenderHierarchy();
    Grid->RenderHierarchy();
    for (size_t i = 0; i < List.size(); i++)
    {
        List[i]->RenderHierarchy();
    }

    //Cam->RenderHierarchy();
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

        vector<Vector3> P;
        vector<Vector2> T;
        vector<Vector3> N;
        vector<UINT> Indices;
        vector<VertexPTN> Vertices;
        string objName = path.substr(0, path.size() - 4);
        Actor* temp = Actor::Create(objName);
        List.push_back(temp);

        while (!fin.eof())
        {
            string Input;
            fin >> Input;
            if (Input[0] == 'm')
            {
                string mtl;
                fin >> mtl;
                mtl = mtl.substr(2, mtl.size());
                ReadMaterial("../Obj/" + mtl);
            }
            else if (Input[0] == 'g')
            {
                static int gCount = -1;
                static string name;
                gCount++;
                if (gCount == 1)
                {
                    fin >> name;
                    

                }
                if (gCount == 2)
                {
                    //버텍랑 인덱스가지고 게임오브젝트 만들기
                    GameObject* temp2
                        = GameObject::Create(name);

                    VertexPTN* copyVertex =
                        new VertexPTN[Vertices.size()];
                    
                    copy(Vertices.begin(), Vertices.end(),
                        stdext::checked_array_iterator<VertexPTN*>
                        (copyVertex, Vertices.size()));

                    UINT* copyIdx =
                        new UINT[Indices.size()];

                    copy(Indices.begin(), Indices.end(),
                        stdext::checked_array_iterator<UINT*>
                        (copyIdx, Indices.size()));

               
                    temp2->mesh
                        = make_shared<Mesh>(copyVertex, Vertices.size(),
                            copyIdx, Indices.size(),VertexType::PTN);
                    temp2->mesh->file = name;
                    temp->AddChild(temp2);
                    temp2->shader = make_shared<Shader>();
                    temp2->shader->LoadFile("3.cube.hlsl");

                    temp2->texture = make_shared<Texture>();
                    temp2->texture->LoadFile("box.jpg");

                    Vertices.clear();
                    Indices.clear();

                    gCount = 0;
                }
            }
            else if (Input[0] == 'v')
            {
                if (Input[1] == 't')
                {
                    Vector2 uv;
                    float temp;
                    fin >> uv.x >> uv.y >> temp;
                    T.push_back(uv);
                }
                else if (Input[1] == 'n')
                {
                    Vector3 nor;
                    fin >> nor.x >> nor.y >> nor.z;
                    N.push_back(nor);
                }
                else
                {
                    Vector3 pos;
                    fin >> pos.x >> pos.y >> pos.z;
                    P.push_back(pos);
                }
            }
            else if (Input[0] == 'f')
            {
                int idx[3]; char slash;
                VertexPTN ptn;
                fin >> idx[0] >> slash >> idx[1] >> slash >> idx[2];
                ptn.position = P[idx[0] - 1];
                ptn.uv = T[idx[1] - 1];
                ptn.normal = N[idx[2] - 1];
                Indices.push_back(Vertices.size());
                Vertices.push_back(ptn);

                fin >> idx[0] >> slash >> idx[1] >> slash >> idx[2];
                ptn.position = P[idx[0] - 1];
                ptn.uv = T[idx[1] - 1];
                ptn.normal = N[idx[2] - 1];
                Indices.push_back(Vertices.size());
                Vertices.push_back(ptn);

                fin >> idx[0] >> slash >> idx[1] >> slash >> idx[2];
                ptn.position = P[idx[0] - 1];
                ptn.uv = T[idx[1] - 1];
                ptn.normal = N[idx[2] - 1];
                Indices.push_back(Vertices.size());
                Vertices.push_back(ptn);
            }
            else
            {
                //한줄 건너뛰기
                char c[128];
                fin.getline(c, 128);
            }
        }

        
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

void Main::ReadMaterial(string file)
{
    ifstream fin;
    fin.open(file, ios::in);
    if (!fin.is_open()) return;

    while (!fin.eof())
    {
        string Input;
        fin >> Input;
        if (Input[0] == 'm')
        {
        }
    }
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