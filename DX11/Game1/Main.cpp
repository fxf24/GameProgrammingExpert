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

    //Sun = Actor::Create();
    //Sun->position.x = 0.0f;
    //Sun->position.y = 0.0f;
    //Sun->scale.x = 1.0f;
    //Sun->scale.y = 1.0f;

    ////Sun.mesh.reset();
    ////Sun.mesh = nullptr;
    //for (int i = 0; i < 5; i++)
    //{
    //    GameObject* SunBone = GameObject::Create("SunBone" + to_string(i));
    //    Sun->AddChild(SunBone);
    //    GameObject* Planet = GameObject::Create("Planet" + to_string(i));
    //    SunBone->AddChild(Planet);

    //    Planet->position.x = 2.0f * (i + 1);
    //    Planet->position.y = 2.0f * (i + 1);

    //    Planet->scale.x = 1.0f;
    //    Planet->scale.y = 1.0f;
    //}
    //


    Temp = Actor::Create();

    Xml::XMLDocument* doc = new Xml::XMLDocument();
    string path = "../Contents/GameObject/Sun.xml";
    Xml::XMLError result = doc->LoadFile(path.c_str());
    if (result != Xml::XML_SUCCESS) return;
    Xml::XMLElement* ob;
    ob = doc->FirstChildElement();

    GenerateXML((GameObject*)Temp, ob);
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
    //Sun->RenderHierarchy();
    Temp->RenderHierarchy();
    ImGui::End();

    Temp->rotation.y += 60.0f * TORADIAN * DELTA;
    //Temp->Find("EarthBone")->rotation.y += 1.0f * TORADIAN * DELTA;s
    //Sun->Find("SunBone2")->rotation.y += 60.0f * TORADIAN * DELTA;

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

void Main::GenerateXML(GameObject* go,Xml::XMLElement* ob)
{
    go->name = ob->Attribute("Name");

    Xml::XMLElement* component;
    if (component = ob->FirstChildElement("Mesh"))
    {
        string file = component->Attribute("File");
        SafeReset(go->mesh);
        go->mesh = RESOURCE->LoadMesh(file);
    }
    if (component = ob->FirstChildElement("Transform"))
    {
        Xml::XMLElement* trans = component->FirstChildElement("Position");
        go->position.x = trans->FloatAttribute("X");
        go->position.y = trans->FloatAttribute("Y");
        go->position.z = trans->FloatAttribute("Z");

        trans = component->FirstChildElement("Scale");
        go->scale.x = trans->FloatAttribute("X");
        go->scale.y = trans->FloatAttribute("Y");
        go->scale.z = trans->FloatAttribute("Z");

        trans = component->FirstChildElement("Rotation");
        go->rotation.x = trans->FloatAttribute("X");
        go->rotation.y = trans->FloatAttribute("Y");
        go->rotation.z = trans->FloatAttribute("Z");
    }

    if (component = ob->FirstChildElement("Children"))
    {
        int size = stoi(component->Attribute("Size"));

        if (size == 0) return;
        for (int i = 0; i < size; i++)
        {
            string child = "Child" + to_string(i);

            GameObject* Child = GameObject::Create(go->name + child);
            go->AddChild(Child);
            if (component = ob->FirstChildElement(child.c_str()))
                GenerateXML(Child, component);
        }
    }
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