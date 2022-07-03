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
}

GameObject* GameObject::Create(string name)
{
	GameObject* temp = new GameObject();
	temp->name = name;
	return temp;
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
		W *= parent->RT;
		RT *= parent->RT;
	}
	//재귀호출
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Update();
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


	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Render();
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

bool GameObject::RenderImGui()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::SliderFloat3("position", (float*)&position, -30.0f, 30.0f);
		ImGui::SliderFloat3("rotation", (float*)&rotation, 0.0f, PI * 2.0f);
		ImGui::SliderFloat3("scale", (float*)&scale, 0.0f, 100.0f);
		
		ImGui::InputText("Child Name", childName, 64);
		if (ImGui::Button("Add Child"))
		{
			AddChild(Create(childName));
			memset(childName, 0, 64);
		}

		Delete();

		for (int i = 0; i < children.size(); i++)
		{
			children[i]->RenderImGui();
		}
		ImGui::TreePop();
	}
	
	return false;
}

void GameObject::AddChild(GameObject* child)
{
	if (root->Find(child->name))
		return;
	if (child->name == "")
		return;

	root->obList[child->name] = child;
	children.push_back(child);
	child->parent = this;
	child->root = root;
}

void GameObject::Delete()
{
	if (ImGui::Button("Delete"))
		ImGui::OpenPopup("Delete?");

	if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");

		if (ImGui::Button("OK", ImVec2(120, 0))) 
		{
			if (root == this)
			{
				ImGui::OpenPopup("Actor");

				bool unused_open = true;
				if (ImGui::BeginPopupModal("Actor"))
				{
					ImGui::Text("Actor can not be deleted.\n");

					if (ImGui::Button("Close"))
						ImGui::CloseCurrentPopup();
					ImGui::EndPopup();
				}
				
				//ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
				return;
			}
			else
			{
				if (!children.empty())
				{
					for (auto c : children)
					{
						c->parent = parent;
						parent->children.push_back(c);
					}
					children.clear();
				}

				auto it = find(parent->children.begin(), parent->children.end(), this);
				parent->children.erase(it);
				root->Delete(name);
				ImGui::CloseCurrentPopup(); 
			}
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) 
		{ 
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::EndPopup();
	}
}

GameObject* Actor::Find(string name)
{
	auto it = obList.find(name);

	if (it != obList.end())
	{
		return it->second;
	}
	return nullptr;
}

Actor* Actor::Create(string name)
{
	Actor* temp = new Actor();
	temp->name = name;
	return temp;
}

void Actor::Delete(string name)
{
	auto it = obList.find(name);
	obList.erase(it);
}
