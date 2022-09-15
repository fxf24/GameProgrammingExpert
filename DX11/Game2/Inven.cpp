#include "stdafx.h"

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
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
		string num = "num" + it->first;
		string img = to_string(it->second->num) + ".png";
		Ui->Find(num)->material->diffuse.w = 1.0f;
		Ui->Find(num)->material->diffuseMap = make_shared<Texture>();
		Ui->Find(num)->material->diffuseMap->
			LoadFile(img);
	}
}

void Inven::Init()
{
	OverName = " ";
	Ui = UI::Create();
	Ui->LoadFile("Window.xml");

	Item* temp = new Item();
	temp->num = 1;
	temp->name = "redPotion";
	temp->imgFile = "2000000.png";
	inven["00"] = temp;
	

	temp = new Item();
	temp->num = 1;
	temp->name = "bluePotion";
	temp->imgFile = "2000003.png";
	inven["01"] = temp;

	temp = new Item();
	temp->num = 1;
	temp->name = "whitePotion";
	temp->imgFile = "2000002.png";
	inven["10"] = temp;

	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["11"] = temp;

	/*for (auto it = inven.begin(); it != inven.end(); it++)
	{


	}*/

	((UI*)Ui->Find("00"))->mouseOver = [&]() {OverName = "00"; };
	((UI*)Ui->Find("01"))->mouseOver = [&]() {OverName = "01"; };
	((UI*)Ui->Find("10"))->mouseOver = [&]() {OverName = "10"; };
	((UI*)Ui->Find("11"))->mouseOver = [&]() {OverName = "11"; };


	((UI*)Ui->Find("00"))->mouseDown = [&]() 
	{Mouse->visible = true; Swap(Mouse->material, Ui->Find("00")->material); };
	((UI*)Ui->Find("01"))->mouseDown = [&]() 
	{Mouse->visible = true; Swap(Mouse->material, Ui->Find("01")->material); };
	((UI*)Ui->Find("10"))->mouseDown = [&]() 
	{Mouse->visible = true; Swap(Mouse->material, Ui->Find("10")->material); };
	((UI*)Ui->Find("11"))->mouseDown = [&]() 
	{Mouse->visible = true; Swap(Mouse->material, Ui->Find("11")->material); };

	((UI*)Ui->Find("00"))->mouseUp = [&]() {Mouse->visible = false; Swap(Mouse->material, Ui->Find(OverName)->material); Swap(Mouse->material, Ui->Find("00")->material); Swap(inven["00"], inven[OverName]);};
	((UI*)Ui->Find("01"))->mouseUp = [&]() {Mouse->visible = false; Swap(Mouse->material, Ui->Find(OverName)->material); Swap(Mouse->material, Ui->Find("01")->material); Swap(inven["01"], inven[OverName]);};
	((UI*)Ui->Find("10"))->mouseUp = [&]() {Mouse->visible = false; Swap(Mouse->material, Ui->Find(OverName)->material); Swap(Mouse->material, Ui->Find("10")->material); Swap(inven["10"], inven[OverName]);};
	((UI*)Ui->Find("11"))->mouseUp = [&]() {Mouse->visible = false; Swap(Mouse->material, Ui->Find(OverName)->material); Swap(Mouse->material, Ui->Find("11")->material); Swap(inven["11"], inven[OverName]);};

	invenUpdate();



	Mouse = UI::Create("Mouse");
	Mouse->shader = Ui->shader;
	Mouse->mesh = Ui->mesh;
	Mouse->visible = false;
}

void Inven::Update()
{
	Ui->Update();
	Mouse->SetWorldPos(INPUT->NDCPosition);
	Mouse->Update();

	ImGui::Begin("Hierarchy");
	Ui->RenderHierarchy();
	Mouse->RenderHierarchy();
	if (ImGui::TreeNode("Inven"))
	{
		for (auto it = inven.begin(); it != inven.end(); it++)
		{
			ImGui::DragInt(it->first.c_str(), &it->second->num);
		}
		ImGui::TreePop();
	}

	ImGui::End();
	invenUpdate();
}

void Inven::Render()
{
	DEPTH->Set(false);
	Ui->Render();
	Mouse->Render();
	DEPTH->Set(true);
}
