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
    App.fixFrame = 1000000;
    Cam = new Camera();
    Camera::main = Cam;

    Grid = Actor::Create();
    Grid->mesh = RESOURCE->LoadMesh("1.Grid.mesh");

    Sun = Actor::Create();
    Sun->position.x = 0.0f;
    Sun->position.y = 0.0f;
    Sun->scale.x = 1.0f;
    Sun->scale.y = 1.0f;

    //Sun.mesh.reset();
    //Sun.mesh = nullptr;
    for (int i = 0; i < 5; i++)
    {
        GameObject* SunBone = GameObject::Create("SunBone" + to_string(i));
        Sun->AddChild(SunBone);
        GameObject* Planet = GameObject::Create("Planet" + to_string(i));
        SunBone->AddChild(Planet);

        Planet->position.x = 2.0f * (i + 1);
        Planet->position.y = 2.0f * (i + 1);

        Planet->scale.x = 1.0f;
        Planet->scale.y = 1.0f;
    }
    //


    Temp = Actor::Create();

    Xml::XMLDocument* doc = new Xml::XMLDocument();
    string path = "../Contents/GameObject/Sun.xml";
    Xml::XMLError result = doc->LoadFile(path.c_str());
    if (result != Xml::XML_SUCCESS) return;
    Xml::XMLElement* ob;
    ob = doc->FirstChildElement();
    Temp->name = ob->Attribute("Name");

    Xml::XMLElement* component;
    if (component = ob->FirstChildElement("Mesh"))
    {
        string file = component->Attribute("File");
        SafeReset(Temp->mesh);
        Temp->mesh = RESOURCE->LoadMesh(file);
    }
    if (component = ob->FirstChildElement("Transform"))
    {
        Xml::XMLElement* trans = component->FirstChildElement("Position");
        Temp->position.x = trans->FloatAttribute("X");
        Temp->position.y = trans->FloatAttribute("Y");
        Temp->position.z = trans->FloatAttribute("Z");

        trans = component->FirstChildElement("Scale");
        Temp->scale.x = trans->FloatAttribute("X");
        Temp->scale.y = trans->FloatAttribute("Y");
        Temp->scale.z = trans->FloatAttribute("Z");

        trans = component->FirstChildElement("Rotation");
        Temp->rotation.x = trans->FloatAttribute("X");
        Temp->rotation.y = trans->FloatAttribute("Y");
        Temp->rotation.z = trans->FloatAttribute("Z");
    }
}

void Main::Release()
{
    RESOURCE->ReleaseAll();
    Sun->Release();
    Grid->Release();
}


void Main::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d",TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Sun->RenderHierarchy();
    ImGui::End();

    //Sun->rotation.y += 60.0f * TORADIAN * DELTA;
    Sun->Find("SunBone2")->rotation.y += 60.0f * TORADIAN * DELTA;

    Cam->Update();
    Grid->Update();
    //Sun->Update();
    Temp->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    Cam->Set();
    Grid->Render();
    //Sun->Render();
    Temp->Render();
}

void Main::ResizeScreen()
{
    Cam->w = App.GetWidth();
    Cam->h = App.GetHeight();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game1");
	App.SetInstance(instance);
	App.InitWidthHeight(1000.0f, 500.0f);
    WIN->Create();
    D3D->Create();
	Main * main = new Main();
    main->Init();
	int wParam = (int)WIN->Run(main);
    main->Release();
	SafeDelete(main);
    D3D->DeleteSingleton();
	WIN->DeleteSingleton();
	return wParam;
}