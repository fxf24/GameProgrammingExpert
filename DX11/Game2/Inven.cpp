#include "stdafx.h"


void Inven::invenUpdate()
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

void Inven::Init()
{
	OverName = " ";
	Ui = UI::Create();
	Ui->LoadFile("Inven.xml");
	//Store = UI::Create();
	//Store->LoadFile("Store.xml");

	Item* temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["00"] = temp;

	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["01"] = temp;

	temp = new Item();
	temp->num = 0;
	temp->name =  " ";
	temp->imgFile = " ";
	inven["10"] = temp;

	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["11"] = temp;

	//Ui->mouseOver = [this]() {OverName = "None"; };
	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		((UI*)Ui->Find(it->first))->mouseOver = [it, this]() {this->OverName = it->first; };
		((UI*)Ui->Find(it->first))->mouseDown = [=]()
		{
			if (INPUT->KeyDown(VK_RBUTTON))
			{
				
			}
			else
			{
				if (inven[it->first]->num > 1)
				{
					Mouse->material = Ui->Find(it->first)->material;
				}
				else if (inven[it->first]->num == 1)
				{
					Util::Swap(Mouse->material, Ui->Find(it->first)->material);
				}
				else
				{
					Util::Swap(Mouse->material, Ui->Find(it->first)->material);
				}
			}
			
		};
		((UI*)Ui->Find(it->first))->mouseUp = [=]()
		{

			Util::Swap(Mouse->material, Ui->Find(it->first)->material);
			if (OverName != "None")
			{
				if (inven[OverName]->num >= 1)
				{
					SOUND->Stop("GOLD");
					SOUND->Play("GOLD");
					inven[OverName]->num--;
					money += 50;
				}
			}
			else
			{
				Mouse->visible = false;

				if (OverName != "None")
				{
					Util::Swap(it->second, inven[OverName]);
				}
			}
			invenUpdate();
		};
	}
	//((UI*)Store->Find("s00"))->mouseDown = [=]()
	//{
	//	for (auto it = inven.begin(); it != inven.end(); it++)
	//	{
	//		if (it->second->num == 0)
	//		{
	//			it->second->num++;
	//			it->second->name = "redpotion";
	//			it->second->imgFile = "2000000.png";
	//			money -= 100;
	//			break;
	//		}
	//		else if(it->second->name == "redpotion")
	//		{
	//			it->second->num++;
	//			money -= 100;
	//			break;
	//		}
	//	}
	//	invenUpdate();

	//	cout << money << endl;
	//}; 
	//((UI*)Store->Find("s01"))->mouseDown = [=]()
	//{
	//	for (auto it = inven.begin(); it != inven.end(); it++)
	//	{
	//		if (it->second->num == 0)
	//		{
	//			it->second->num++;
	//			it->second->name = "bluepotion";
	//			it->second->imgFile = "2000003.png";
	//			money -= 100;
	//			break;
	//		}
	//		else if (it->second->name == "bluepotion")
	//		{
	//			it->second->num++;
	//			money -= 100;
	//			break;
	//		}
	//	}
	//	invenUpdate();

	//	cout << money << endl;
	//};



	invenUpdate();
	Mouse = UI::Create("Mouse");
	Mouse->shader = Ui->shader;
	Mouse->mesh = Ui->mesh;
	Mouse->visible = false;
	Mouse->scale = Vector3(0.2f, 0.2f, 0.2f);
}

void Inven::Update()
{
	

	ImGui::Begin("Hierarchy");
	ImGui::Checkbox("show", &show);
	Ui->RenderHierarchy();
	//Store->RenderHierarchy();
	Mouse->RenderHierarchy();
	ImGui::End();

	if (not show) return;

	Ui->Update();
	//Store->Update();

	Mouse->SetWorldPos(INPUT->NDCPosition);
	Mouse->Update();
}

void Inven::Render()
{
	if (not show) return;

	DEPTH->Set(false);
	Ui->Render();
	//Store->Render();
	Mouse->Render();
	DEPTH->Set(true);


	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		if (it->second->num > 0)
		{
			string number = "num" + it->first;
			Vector2 pos = Vector2(Ui->Find(number)->GetWorldPos().x + 1.0f, 1.0f - Ui->Find(number)->GetWorldPos().y);
			pos.x *= App.GetHalfWidth();
			pos.y *= App.GetHalfHeight();

			//깊이 렌더링  off
		//         l  t  r   b
			RECT rc{ pos.x, pos.y, pos.x + 30, pos.y + 30 };
			//                    출력할 문자열,텍스트박스 크기위치

			DWRITE->RenderText(to_wstring(inven[it->first]->num), rc, 30, L"Verdana", Color(1, 0, 0, 1),
				DWRITE_FONT_WEIGHT_BOLD);
		}
	}
	
	string number = "num11";
	Vector2 pos = Vector2(Ui->Find(number)->GetWorldPos().x + 1.0f, 1.0f - Ui->Find(number)->GetWorldPos().y);
	pos.x *= App.GetHalfWidth();
	pos.y *= App.GetHalfHeight();
	RECT rc{ pos.x - 200, pos.y + 30, pos.x + 1000, pos.y + 1000};
	
	wstring temp = L"소지금: " + to_wstring(money);
	DWRITE->RenderText(temp, rc, 30, L"Verdana", Color(1, 0, 0, 1),
		DWRITE_FONT_WEIGHT_BOLD);
}
