#include "framework.h"


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
			return true; //�����ڽı����� �������� �ʱ�
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
	ImGui::Checkbox("visible", &visible);
	if (ImGui::BeginTabBar("MyTabBar"))
	{
		if (ImGui::BeginTabItem("Transform"))
		{
			ImGui::DragFloat3("position", (float*)&position,0.05f);
			ImGui::DragFloat3("rotation", (float*)&rotation, 0.05f, 0.0f, PI * 2.0f);
			ImGui::DragFloat3("scale", (float*)&scale, 0.05f);
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
			if (ImGui::Button("Delete"))
			{
				SafeReset(mesh);
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
				Save(path);
			}
			ImGui::SameLine();
			if (GUI->FileImGui("Load", "Load Actor",
				".xml", "../Contents/GameObject"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				Load(path);
			}


			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}


}