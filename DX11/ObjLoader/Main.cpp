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
                    if (Input[1] == 'n')
                    {

                    }
                    else
                    {
                        Vector3 pos;
                        fin >> pos.x >> pos.y >> pos.z;
                    }
                }
                //f일때 ex) 1/10/1 posision/uv/normal index number
                else 
                {

                }
            }
        }

        Actor* temp = Actor::Create(path);
        //temp->mesh = new Mesh();
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