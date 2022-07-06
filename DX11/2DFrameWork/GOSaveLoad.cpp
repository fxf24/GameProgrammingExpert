#include "framework.h"

void Actor::Save(string file)
{
	this->file = file;
	Xml::XMLDocument* doc = new Xml::XMLDocument();
	Xml::XMLElement* ob = doc->NewElement("Root");
	doc->LinkEndChild(ob);
	ob->SetAttribute("Name", name.c_str());
	ob->SetAttribute("isVisible", visible);

	Xml::XMLElement* Mesh = doc->NewElement("Mesh");
	ob->LinkEndChild(Mesh);
	Mesh->SetAttribute("File", mesh->file.c_str());

	Xml::XMLElement* Position = doc->NewElement("Position");
	Mesh->LinkEndChild(Position);
	Position->SetAttribute("X", position.x);
	Position->SetAttribute("Y", position.y);
	Position->SetAttribute("Z", position.z);

	string path = "../Contents/GameObject/" + file;
	doc->SaveFile(path.c_str());

	SafeDelete(doc);

}

void Actor::Load(string file)
{
	this->file = file;
	Xml::XMLDocument* doc = new Xml::XMLDocument();
	string path = "../Contents/GameObject/" + file;
	Xml::XMLError result = doc->LoadFile(path.c_str());
	if (result != Xml::XML_SUCCESS) return;

	//기존멤버지우기
	ReleaseMember();

	Xml::XMLElement* ob;
	ob = doc->FirstChildElement();
	name = ob->Attribute("Name");
	obList[name] = this;
	LoadObject(ob, doc);
	SafeDelete(doc);
}

void GameObject::SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc)
{
}

void GameObject::LoadObject(Xml::XMLElement* This, Xml::XMLDocument* doc)
{
	Xml::XMLElement* component;
	Xml::XMLElement* transform;
	string file;

	visible = This->BoolAttribute("isVisible");

	if (component = This->FirstChildElement("Mesh"))
	{
		file = component->Attribute("File");
		SafeReset(mesh);
		mesh = RESOURCE->LoadMesh(file);
	}
	if (component = This->FirstChildElement("Shader"))
	{
		file = component->Attribute("File");
		SafeReset(shader);
		shader = RESOURCE->LoadShader(file);
	}


	component = This->FirstChildElement("Transform");
	transform = component->FirstChildElement("Position");
	position.x = transform->FloatAttribute("X");
	position.y = transform->FloatAttribute("Y");
	position.z = transform->FloatAttribute("Z");

	transform = component->FirstChildElement("Scale");
	scale.x = transform->FloatAttribute("X");
	scale.y = transform->FloatAttribute("Y");
	scale.z = transform->FloatAttribute("Z");
	transform = component->FirstChildElement("Rotation");
	rotation.x = transform->FloatAttribute("X");
	rotation.y = transform->FloatAttribute("Y");
	rotation.z = transform->FloatAttribute("Z");

	//child.resize(5);
	component = This->FirstChildElement("Children");
	int size = component->IntAttribute("Size");

	for (int i = 0; i != size; i++)
	{
		string Tag = "Child" + to_string(i);
		Xml::XMLElement* ob = This->FirstChildElement(Tag.c_str());
		string childName = ob->Attribute("Name");
		GameObject* temp = GameObject::Create(childName);
		AddChild(temp);
		temp->LoadObject(ob, doc);
	}
}
