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

    ImGui::Begin("AssimpImporter");

    if (GUI->FileImGui("AssimpImporter", "Importer",
        ".fbx,.obj,.x", "../Assets"))
    {
        string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
        string file = "../Assets/" + path;
        
        Assimp::Importer importer; //지역변수로 선언된 객체

       const aiScene* scene = importer.ReadFile
        (
            file,
            aiProcess_ConvertToLeftHanded
            | aiProcess_Triangulate
            | aiProcess_GenUVCoords
            | aiProcess_GenNormals
            | aiProcess_CalcTangentSpace
        );
        assert(scene != NULL and "Import Error");

        Actor* temp = Actor::Create(scene->mRootNode->mName.C_Str());
        temp->mesh = RESOURCE->meshes.Load("2.Sphere.mesh");
        temp->shader = RESOURCE->shaders.Load("2.cube.hlsl");
        ReadNode(temp, scene->mRootNode);
        List.push_back(temp);
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

void Main::ReadNode(GameObject* dest, aiNode* src)
{
    Matrix tempMat = ToMatrix(src->mTransformation);
    Vector3 s, r, t; Quaternion q;
    tempMat.Decompose(s, q, t);
    r = Util::QuaternionToYawPtichRoll(q);
    dest->scale = s; dest->rotation = r; dest->SetLocalPos(t);

    //자식노드들로 재귀호출
    for (UINT i = 0; i < src->mNumChildren; i++)
    {
        GameObject* temp =
            GameObject::Create(src->mChildren[i]->mName.C_Str());
        dest->AddChild(temp);
        temp->mesh = RESOURCE->meshes.Load("2.Sphere.mesh");
        temp->shader = RESOURCE->shaders.Load("2.cube.hlsl");
        ReadNode(temp, src->mChildren[i]);
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