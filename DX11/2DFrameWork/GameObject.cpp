#include "framework.h"

GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	parent = nullptr;
	root = nullptr;
	visible = true;

	shader = RESOURCE->LoadShader("1.Cube.hlsl");
	mesh = RESOURCE->LoadMesh("1.Sphere.mesh");
}
Actor::Actor()
{
	root = this;
}


GameObject::~GameObject()
{
	SafeReset(mesh);
	SafeReset(shader);
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

void GameObject::Update()
{
	//if (not active)return;



	S = Matrix::CreateScale(scale.x, scale.y, scale.z);
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	T = Matrix::CreateTranslation(position.x, position.y, position.z);
	RT = R * T;
	W = S * RT;
	if (parent)
	{
		S = S * parent->S;
		RT *= parent->RT;
		W *= parent->W;
	}
	//재귀호출
	for (auto it = children.begin(); it != children.end(); it++)
	{
		it->second->Update();
	}

}

void GameObject::Render()
{
	Matrix TW = W.Transpose();
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D->GetDC()->Map(WBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy_s(mappedResource.pData, sizeof(Matrix), &TW, sizeof(Matrix));
	D3D->GetDC()->Unmap(WBuffer, 0);
	
	if (visible)
	{
		//GameObject::Render();
		shader->Set();
		if (mesh)
		{
			mesh->Set();
			D3D->GetDC()->DrawIndexed(mesh->indexCount, 0, 0);
		}
	}


	for (auto it = children.begin(); it != children.end(); it++)
	{
		it->second->Render();
	}
}


ID3D11Buffer* GameObject::WBuffer = nullptr;
void GameObject::CreateStaticMember()
{
	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = sizeof(Matrix);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &WBuffer);
	assert(SUCCEEDED(hr));

	D3D->GetDC()->VSSetConstantBuffers(0, 1, &WBuffer);
}

void GameObject::DeleteStaticMember()
{
	SafeRelease(WBuffer);
}

bool GameObject::RenderHierarchy()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		if (ImGui::IsItemToggledOpen() or
			ImGui::IsItemClicked())
		{
			GUI->target = this;
		}
		static char childName[32] = "None";
		ImGui::InputText("childName", childName, 32);

		if (ImGui::Button("addChid"))
		{
			AddChild(GameObject::Create(childName));
		}
		ImGui::SameLine();
		if (ImGui::Button("delete"))
		{
			root->DeleteObject(name);
			GUI->target = nullptr;
			ImGui::TreePop();
			return true; //하위자식까지는 접근하지 않기
		}
		// l->r
		for (auto it = children.begin(); it != children.end(); it++)
		{
			if (it->second->RenderHierarchy())
			{
				ImGui::TreePop();
				GUI->target = nullptr;
				return true;
			}
		}
		ImGui::TreePop();
	}
	return false;
}

void GameObject::RenderDetail()
{
	ImGui::Text(name.c_str());
	if (ImGui::BeginTabBar("MyTabBar"))
	{
		if (ImGui::BeginTabItem("Transform"))
		{
			ImGui::SliderFloat3("position", (float*)&position, -30.0f, 30.0f);
			ImGui::SliderFloat3("rotation", (float*)&rotation, 0.0f, PI * 2.0f);
			ImGui::SliderFloat3("scale", (float*)&scale, 0.0f, 10.0f);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Mesh"))
		{
			if (mesh)
			{
				ImGui::Text(mesh->file.c_str());
			}
			if (GUI->FileImGui("Save", "Save Mesh",
				".mesh", "../Contents/Mesh"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				mesh->SaveFile(path);
			}
			ImGui::SameLine();
			if (GUI->FileImGui("Load", "Load Mesh",
				".mesh", "../Contents/Mesh"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				SafeReset(mesh);
				mesh = RESOURCE->LoadMesh(path);
			}
			ImGui::SameLine();
			if(ImGui::Button("Delete"))
			{
				SafeReset(mesh);
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
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

void Actor::Release()
{
	for (auto it = children.begin();it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}

Actor* Actor::Create(string name)
{
	Actor* temp = new Actor();
	temp->name = name;
	return temp;
}

GameObject* Actor::Find(string name)
{
	auto it = obList.find(name);
	//찾았다
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

	//지워질대상,지워질대상의 부모 포인터
	GameObject* Target = temp->second;
	GameObject* Parent = temp->second->parent;
	//부모리스트에서 타겟 비우기
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
