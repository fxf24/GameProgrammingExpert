#include "stdafx.h"
#include "Main.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

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
        string usemtl;
        string mtlfile;
        //파일 열기
        ifstream fin;
        fin.open(file, ios::in);
        if (!fin.is_open()) return;

        vector<Vector3> P;
        vector<Vector2> T;
        vector<Vector3> N;
        vector<UINT> Indices;
        vector<VertexPTN> Vertices;
        int gCount = -1;
        objName = path.substr(0, path.size() - 4);
        Actor* temp = Actor::Create(objName);
        List.push_back(temp);

        while (!fin.eof())
        {
            string Input;
            fin >> Input;
            if (Input[0] == 'm')
            {
              
                fin >> mtlfile;
                mtlfile = mtlfile.substr(2, mtlfile.size());
                ReadMaterial(mtlfile);
            }
            else if (Input[0] == 'g')
            {
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
                    //"../Contents/Mesh/" + "a";
                    string checkPath = "../Contents/Mesh/" + objName;
                    if (!PathFileExistsA(checkPath.c_str()))
                    {
                        CreateDirectoryA(checkPath.c_str(), NULL);
                    }
                    temp2->mesh->SaveFile(objName + "/3." + name + ".mesh");
                    temp->AddChild(temp2);
                    temp2->shader = make_shared<Shader>();
                    temp2->shader = RESOURCE->shaders.Load("3.cube.hlsl");
                    temp2->material = make_shared<Material>();
                    temp2->material = RESOURCE->materials.Load(objName +"/"+usemtl + ".mtl");
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
            else if (Input[0] == 'u')
            {
                fin >> usemtl;
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
    string mtlfile;
    Material temp;
    fin.open("../Obj/" + file, ios::in);
    if (!fin.is_open()) return;

    while (!fin.eof())
    {
        string Input;
        fin >> Input;
        if (Input[0] == 'n')
        {
            fin >> mtlfile;
        }
        else if (Input[0] == 'K')
        {
            if (Input[1] == 'a')
            {
                fin >> temp.ambient.x;
                fin >> temp.ambient.y;
                fin >> temp.ambient.z;
                //매핑텍스쳐가 있는가?
                temp.ambient.w = 0.0f;
            }
            else if (Input[1] == 'd')
            {
                fin >> temp.diffuse.x;
                fin >> temp.diffuse.y;
                fin >> temp.diffuse.z;
                temp.diffuse.w = 0.0f;
            }
            else if (Input[1] == 's')
            {
                fin >> temp.specular.x;
                fin >> temp.specular.y;
                fin >> temp.specular.z;
                temp.specular.w = 0.0f;
            }
        }
        else if (Input[0] == 'd')
        {
            fin >> temp.opacity;
        }
        else if (Input[0] == 'i')
        {
            fin >> temp.shininess;
        }
        else if (Input[0] == 'm')
        {

            temp.diffuse.w = 1.0f;
            temp.diffuseMap = make_shared<Texture>();
            string textureFile;
            fin >> textureFile;
            size_t tok = file.find_last_of(".");
            string checkPath = "../Contents/Texture/" + objName;
            if (!PathFileExistsA(checkPath.c_str()))
            {
                CreateDirectoryA(checkPath.c_str(), NULL);
            }
            string orgin = "../Obj/" + textureFile;
            string copy = "../Contents/Texture/" + objName + "/" + textureFile;
            bool isCheck = true;
            CopyFileA(orgin.c_str(), copy.c_str(), isCheck);
            temp.diffuseMap->LoadFile(objName + "/" + textureFile);

            checkPath = "../Contents/Material/" + objName;
            if (!PathFileExistsA(checkPath.c_str()))
            {
                CreateDirectoryA(checkPath.c_str(), NULL);
            }
            temp.SaveFile(objName + "/" + mtlfile+".mtl");
        }
        else
        {
            //한줄 건너뛰기
            char c[128];
            fin.getline(c, 128);
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