#include "framework.h"

void Transform::RenderImGui()
{
	ImGui::Checkbox("WorldPos", &worldPos);
	if (worldPos)
	{
		//get
		Vector3 wol = GetWorldPos();
		if (ImGui::DragFloat3("WorldPos", (float*)&wol, 0.05f))
			//set
			SetWorldPos(wol);
	}
	else
	{
		Vector3 loc = GetLocalPos();
		if (ImGui::DragFloat3("LocalPos", (float*)&loc, 0.05f))
			SetLocalPos(loc);
	}


	ImGui::SliderAngle("rotationX", &rotation.x);
	ImGui::SliderAngle("rotationY", &rotation.y);
	ImGui::SliderAngle("rotationZ", &rotation.z);
	ImGui::DragFloat3("scale", (float*)&scale, 0.05f);
}

bool GameObject::RenderHierarchy()
{
	ImGui::PushID(this);
	if (ImGui::TreeNode(name.c_str()))
	{
		if (ImGui::IsItemToggledOpen() or
			ImGui::IsItemClicked())
		{
			GUI->target = this;
		}
		if (ImGui::Button("addChild"))
		{
			ImGui::OpenPopup("childName");
		}
		if (ImGui::BeginPopup("childName"))
		{
			static char childName[32] = "None";
			ImGui::InputText("childName", childName, 32);
			if (ImGui::Button("Create"))
			{
				AddChild(GameObject::Create(childName));
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("delete"))
		{
			root->DeleteObject(name);
			GUI->target = nullptr;
			ImGui::TreePop();
			ImGui::PopID();
			return true; //하위자식까지는 접근하지 않기
		}
		// l->r
		for (auto it = children.begin(); it != children.end(); it++)
		{
			if (it->second->RenderHierarchy())
			{
				ImGui::TreePop();
				ImGui::PopID();
				GUI->target = nullptr;
				return true;
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
	return false;
}

void GameObject::RenderDetail()
{
	ImGui::Text(name.c_str());
	ImGui::Checkbox("visible", &visible);
	if (ImGui::BeginTabBar("MyTabBar"))
	{
		if (ImGui::BeginTabItem("Transform"))
		{
			Transform::RenderImGui();
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
				mesh = RESOURCE->meshes.Load(path);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete"))
			{
				SafeReset(mesh);
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Shader"))
		{
			if (shader)
			{
				ImGui::Text(shader->file.c_str());
			}
			if (GUI->FileImGui("Load", "Load Shader",
				".hlsl", "../Shaders"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				SafeReset(shader);
				shader = RESOURCE->shaders.Load(path);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete"))
			{
				SafeReset(shader);
			}
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}
void Actor::RenderDetail()
{
	GameObject::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar2"))
	{
		if (ImGui::BeginTabItem("Actor"))
		{
			if (GUI->FileImGui("Save", "Save Actor",
				".xml", "../Contents/GameObject"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				SaveFile(path);
			}
			ImGui::SameLine();
			if (GUI->FileImGui("Load", "Load Actor",
				".xml", "../Contents/GameObject"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				LoadFile(path);
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}