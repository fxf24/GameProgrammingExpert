#include "framework.h"
void Actor::SaveFile(string file)
{
	this->file = file;
	Xml::XMLDocument* doc = new Xml::XMLDocument();
	Xml::XMLElement* ob = doc->NewElement("Root");
	doc->LinkEndChild(ob);

	SaveObject(ob, doc);
	string path = "../Contents/GameObject/" + file;
	doc->SaveFile(path.c_str());
	SafeDelete(doc);
}

void Actor::LoadFile(string file)
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
	type = (ObType)ob->IntAttribute("ObType");
	obList[name] = this;
	LoadObject(ob);
	SafeDelete(doc);
}


void GameObject::SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc)
{
	This->SetAttribute("Name", name.c_str());
	This->SetAttribute("Visible", visible);
	This->SetAttribute("ObType", (int)type);
	if (mesh)
	{
		Xml::XMLElement* Mesh = doc->NewElement("Mesh");
		This->LinkEndChild(Mesh);
		Mesh->SetAttribute("File", mesh->file.c_str());
	}
	if (shader)
	{
		Xml::XMLElement* Shader = doc->NewElement("Shader");
		This->LinkEndChild(Shader);
		Shader->SetAttribute("File", shader->file.c_str());
	}
	if (material)
	{
		Xml::XMLElement* Material = doc->NewElement("Material");
		This->LinkEndChild(Material);
		Material->SetAttribute("File", material->file.c_str());
	}
	Transform::SaveTransform(This, doc);

	if (type == ObType::Camera)
	{
		Xml::XMLElement* Cam = doc->NewElement("Camera");
		This->LinkEndChild(Cam);
		Camera* CamOb = dynamic_cast<Camera*>(this);
		Cam->SetAttribute("Ortho", CamOb->ortho);
		Cam->SetAttribute("Fov", CamOb->fov);
		Cam->SetAttribute("Width", CamOb->width);
		Cam->SetAttribute("Height", CamOb->height);
		Cam->SetAttribute("NearZ", CamOb->nearZ);
		Cam->SetAttribute("FarZ", CamOb->farZ);
		Cam->SetAttribute("viewportX", CamOb->viewport.x);
		Cam->SetAttribute("viewportY", CamOb->viewport.y);
		Cam->SetAttribute("viewportW", CamOb->viewport.width);
		Cam->SetAttribute("viewportH", CamOb->viewport.height);
	}

	Xml::XMLElement* Chidren = doc->NewElement("Children");
	This->LinkEndChild(Chidren);
	Chidren->SetAttribute("Size", (int)children.size());
	int i = 0;
	for (auto it = children.begin(); it != children.end(); it++)
	{
		string temp = "Child" + to_string(i++);
		Xml::XMLElement* Child = doc->NewElement(temp.c_str());
		This->LinkEndChild(Child);
		it->second->SaveObject(Child, doc);
	}
}

void GameObject::LoadObject(Xml::XMLElement* This)
{
	Xml::XMLElement* component;
	string file;
	visible = This->BoolAttribute("Visible");


	if (component = This->FirstChildElement("Mesh"))
	{
		file = component->Attribute("File");
		SafeReset(mesh);
		mesh = RESOURCE->meshes.Load(file);
	}
	if (component = This->FirstChildElement("Shader"))
	{
		file = component->Attribute("File");
		SafeReset(shader);
		shader = RESOURCE->shaders.Load(file);
	}
	if (component = This->FirstChildElement("Material"))
	{
		file = component->Attribute("File");
		SafeReset(material);
		material = RESOURCE->materials.Load(file);
	}

	if (type == ObType::Camera)
	{
		Camera* CamOb = dynamic_cast<Camera*>(this);
		component = This->FirstChildElement("Camera");

		CamOb->ortho = component->BoolAttribute("Ortho");
		CamOb->fov = component->FloatAttribute("Fov");
		CamOb->width = component->FloatAttribute("Width");
		CamOb->height = component->FloatAttribute("Height");
		CamOb->nearZ = component->FloatAttribute("NearZ");
		CamOb->farZ = component->FloatAttribute("FarZ");
		CamOb->viewport.x = component->FloatAttribute("viewportX");
		CamOb->viewport.y = component->FloatAttribute("viewportY");
		CamOb->viewport.width = component->FloatAttribute("viewportW");
		CamOb->viewport.height = component->FloatAttribute("viewportH");

	}

	Transform::LoadTransform(This);

	component = This->FirstChildElement("Children");
	int size = component->IntAttribute("Size");

	for (int i = 0; i != size; i++)
	{
		string Tag = "Child" + to_string(i);
		Xml::XMLElement* ob = This->FirstChildElement(Tag.c_str());
		string childName = ob->Attribute("Name");
		ObType Type = (ObType)ob->IntAttribute("ObType");
		if (Type == ObType::GameObject)
		{
			GameObject* temp = GameObject::Create(childName);
			AddChild(temp);
			temp->LoadObject(ob);
		}
		else if (Type == ObType::Actor)
		{
			Actor* temp = Actor::Create(childName);
			AddChild(temp);
			temp->LoadObject(ob);
		}
		else if (Type == ObType::Camera)
		{
			Camera* temp = Camera::Create(childName);
			AddChild(temp);
			temp->LoadObject(ob);
		}
	}
}
void Transform::SaveTransform(Xml::XMLElement* This, Xml::XMLDocument* doc)
{
	Xml::XMLElement* Trans = doc->NewElement("Transform");
	Xml::XMLElement* Pos = doc->NewElement("Position");
	Xml::XMLElement* Scale = doc->NewElement("Scale");
	Xml::XMLElement* Rot = doc->NewElement("Rotation");
	This->LinkEndChild(Trans);
	Trans->LinkEndChild(Pos);
	Trans->LinkEndChild(Scale);
	Trans->LinkEndChild(Rot);
	Pos->SetAttribute("X", position.x);
	Pos->SetAttribute("Y", position.y);
	Pos->SetAttribute("Z", position.z);
	Scale->SetAttribute("X", scale.x);
	Scale->SetAttribute("Y", scale.y);
	Scale->SetAttribute("Z", scale.z);
	Rot->SetAttribute("X", rotation.x);
	Rot->SetAttribute("Y", rotation.y);
	Rot->SetAttribute("Z", rotation.z);
}

void Transform::LoadTransform(Xml::XMLElement* This)
{
	Xml::XMLElement* component;
	Xml::XMLElement* transform;
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
}

