#include "framework.h"

GameObject::GameObject()
{
	type = ObType::GameObject;
	root = nullptr;
	visible = true;
	//shader = RESOURCE->shaders.Load("1.Cube.hlsl");
		// = RESOURCE->LoadShader("1.Cube.hlsl");
	//mesh = RESOURCE->LoadMesh("1.Sphere.mesh");
	//mesh = make_shared<Mesh>();
	mesh = nullptr;
	shader = nullptr;
	material = nullptr;
	collider = nullptr;
}
Actor::Actor()
{
	type = ObType::Actor;
	root = this;
	skeleton = nullptr;
	//boneIndex = 0;
}


GameObject::~GameObject()
{
	SafeReset(mesh);
	SafeReset(shader);
	SafeReset(material);
	SafeDelete(collider);
}


GameObject* GameObject::Create(string name)
{
	GameObject* temp = new GameObject();
	temp->name = name;
	return temp;
}

void GameObject::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}


void Actor::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}

void Actor::ReleaseMember()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		it->second->Release();
	}
	SafeReset(mesh);
	SafeReset(shader);
	SafeReset(material);
	SafeDelete(collider);
	obList.clear();
	children.clear();
}

Actor* Actor::Create(string name)
{
	Actor* temp = new Actor();
	temp->name = name;
	return temp;
}


void GameObject::Update()
{
	Transform::Update();
	if (boneIndex != -1)
	{
		//
		Matrix temp = root->skeleton->bonesOffset[boneIndex]*W;
		//��켱->���켱
		root->skeleton->bones[boneIndex] = temp.Transpose();
	}

	if (collider)
		collider->Update(this);

	for (auto it = children.begin(); it != children.end(); it++)
		it->second->Update();
}

void GameObject::Render()
{
	if (visible)
	{
		if (mesh and shader)
		{
			Transform::Set();
			shader->Set();
			mesh->Set();

			if (material)
				material->Set();
			else
				defalutMaterial->Set();

			D3D->GetDC()->DrawIndexed(mesh->indexCount, 0, 0);
		}

		for (auto it = children.begin(); it != children.end(); it++)
		{
			it->second->Render();
		}
	}

	if (collider)
		collider->Render();

	if (GUI->target == this)
	{
		if (!parent)
			axis->W = axis->S * T;
		else if (worldPos)
			axis->W = axis->S * Matrix::CreateTranslation(GetWorldPos());
		else
			axis->W = axis->S * T * parent->W;

		axis->Render();
	}

}


GameObject* GameObject::axis = nullptr;
Material* GameObject::defalutMaterial = nullptr;
void GameObject::CreateStaticMember()
{
	axis = new GameObject();
	axis->mesh = RESOURCE->meshes.Load("1.Transform.mesh");
	axis->shader  = RESOURCE->shaders.Load("1.Cube.hlsl");
	axis->S = Matrix::CreateScale(Vector3(500.0f, 500.0f, 500.0f));
	defalutMaterial = new Material();
}

void GameObject::DeleteStaticMember()
{
	SafeDelete(axis);
	SafeDelete(defalutMaterial);
}

void GameObject::AddChild(GameObject* child)
{
	if (root->Find(child->name))
		return;
	root->obList[child->name] = child;
	children[child->name] = child;
	child->parent = this;
	child->root = root;
}
void GameObject::AddBone(GameObject* child)
{
	if (root->Find(child->name))
		return;
	child->boneIndex = ++root->boneIndexCount;
	root->obList[child->name] = child;
	children[child->name] = child;
	child->parent = this;
	child->root = root;
}


GameObject* Actor::Find(string name)
{
	auto it = obList.find(name);
	//ã�Ҵ�
	if (it != obList.end())
	{
		return it->second;
	}
	return nullptr;
}

bool Actor::DeleteObject(string Name)
{
	if (Name == name) return false;

	auto temp = obList.find(Name);

	if (temp == obList.end())  return false;

	//���������,����������� �θ� ������
	GameObject* Target = temp->second;
	GameObject* Parent = temp->second->parent;
	//�θ𸮽�Ʈ���� Ÿ�� ����
	Parent->children.erase(Parent->children.find(Name));

	for (auto it = Target->children.begin();
		it != Target->children.end(); it++)
	{
		Parent->children[it->second->name] = it->second;
		it->second->parent = Parent;
		//SafeRelease(it->second);
	}
	SafeDelete(Target);
	obList.erase(temp);
	return true;
}
