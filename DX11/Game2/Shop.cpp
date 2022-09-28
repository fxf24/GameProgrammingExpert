#include "stdafx.h"

void Shop::invenUpdate()
{
	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		if (it->second->num > 0)
		{
			SafeReset(Ui->Find(it->first)->material->diffuseMap);
			Ui->Find(it->first)->material->diffuse.w = 1.0f;
			Ui->Find(it->first)->material->diffuseMap = make_shared<Texture>();
			Ui->Find(it->first)->material->diffuseMap->
				LoadFile(it->second->imgFile);
		}
		else
		{
			SafeReset(Ui->Find(it->first)->material->diffuseMap);
			Ui->Find(it->first)->material->diffuse.w = 0.0f;
			inven[it->first]->name = " ";
			inven[it->first]->imgFile = " ";
		}
	}
}

void Shop::Init(Inven* pInven)
{
	Ui = UI::Create();
	Ui->LoadFile("Store.xml");


	Item* temp = new Item();
	temp->num = 10;
	temp->name = "redpotion";
	temp->imgFile = "2000000.png";
	inven["s00"] = temp;


	temp = new Item();
	temp->num = 10;
	temp->name = "bluepotion";
	temp->imgFile = "2000003.png";
	inven["s01"] = temp;



	//Ui->mouseOver = [this]() {OverName = "None"; };
	

	this->pInven = pInven;
	invenUpdate();
}

void Shop::Update()
{
	ImGui::Begin("Hierarchy");
	ImGui::Checkbox("show", &show);
	Ui->RenderHierarchy();
	ImGui::End();

	if (not show) return;
	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		UI* temp = (UI*)Ui->Find(it->first);
		if (temp->MouseOver() and INPUT->KeyDown(VK_RBUTTON))
		{
			for (auto it2 = pInven->inven.begin(); it2 != pInven->inven.end(); it2++)
			{
				if (it2->second->num == 0)
				{
					it2->second->num++;
					it2->second->name = it->second->name;
					it2->second->imgFile = it->second->imgFile;
					pInven->money -= 100;
					pInven->invenUpdate();
					break;
				}
				else if (it->second->name == it2->second->name)
				{
					it2->second->num++;
					pInven->money -= 100;
					pInven->invenUpdate();
					break;
				}
			}
		}
	}


	Ui->Update();
}

void Shop::Render()
{
	if (not show) return;

	DEPTH->Set(false);
	Ui->Render();
	DEPTH->Set(true);
}
