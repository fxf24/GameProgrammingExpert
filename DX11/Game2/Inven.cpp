#include "stdafx.h"

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
void Move(T& a, T& b)
{
	a = b;
}

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
	Ui->LoadFile("Window.xml");

	Item* temp = new Item();
	temp->num = 5;
	temp->name = "redPotion";
	temp->imgFile = "2000000.png";
	inven["00"] = temp;


	temp = new Item();
	temp->num = 5;
	temp->name = "bluePotion";
	temp->imgFile = "2000003.png";
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
			Mouse->visible = true;
			if (inven[it->first]->num > 1)
			{
				Move(Mouse->material, Ui->Find(it->first)->material);
				inven[it->first]->num--;
			}
			else if (inven[it->first]->num == 1)
			{
				Swap(Mouse->material, Ui->Find(it->first)->material);
				inven[it->first]->num--;
			}
			else
			{
				Swap(Mouse->material, Ui->Find(it->first)->material);
			}
		};
		((UI*)Ui->Find(it->first))->mouseUp = [=]()
		{
			Mouse->visible = false;


			Swap(Mouse->material, Ui->Find(it->first)->material);
			if (OverName != "None")
			{
				//  second <- > second
				
				if (inven[OverName]->name == " " && inven[OverName]->imgFile == " ")
				{
					inven[OverName]->name = it->second->name;
					inven[OverName]->imgFile = it->second->imgFile;
					inven[OverName]->num++;
				}
				else if (inven[OverName]->name == it->second->name && inven[OverName]->imgFile == it->second->imgFile)
				{
					inven[OverName]->name = it->second->name;
					inven[OverName]->imgFile = it->second->imgFile;
					inven[OverName]->num++;
				}
				else
				{
					Swap(it->second, inven[OverName]);
					inven[OverName]->num++;
				}
			}

			invenUpdate();
		};
	}


	invenUpdate();
	Mouse = UI::Create("Mouse");
	Mouse->shader = Ui->shader;
	Mouse->mesh = Ui->mesh;
	Mouse->visible = false;
	Mouse->scale = Vector3(0.2f, 0.2f, 0.2f);
}

void Inven::Update()
{
	Ui->Update();

	Mouse->SetWorldPos(INPUT->NDCPosition);
	Mouse->Update();

	ImGui::Begin("Hierarchy");
	Ui->RenderHierarchy();
	Mouse->RenderHierarchy();
	ImGui::End();
}

void Inven::Render()
{
	DEPTH->Set(false);
	Ui->Render();
	Mouse->Render();
	DEPTH->Set(true);


	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		string number = "num" + it->first;
		float scalex = Ui->Find(number)->scale.x;
		float scaley = Ui->Find(number)->scale.y;
		Vector2 pos = Vector2(Ui->Find(number)->GetWorldPos().x + 1.0f, 1.0f - Ui->Find(number)->GetWorldPos().y);
		pos.x *= App.GetWidth() / 2.0f;
		pos.y *= App.GetHeight() / 2.0f;

		//깊이 렌더링  off
	//         l  t  r   b
		RECT rc{ pos.x, pos.y, pos.x + 30, pos.y + 30 };
		//                    출력할 문자열,텍스트박스 크기위치
		string prt = to_string(inven[it->first]->num);
		wstring wt;
		wt.assign(prt.begin(), prt.end());
		DWRITE->RenderText(wt, rc, 30, L"Verdana", Color(1, 0, 0, 1),
			DWRITE_FONT_WEIGHT_BOLD);
	}
	
}
