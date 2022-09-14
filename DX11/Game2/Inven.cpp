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
			Ui->Find(it->first)->material->diffuseMap->LoadFile(it->second->imgFile);
		}
	}
}

void Inven::Init()
{
	Ui = UI::Create();
	Ui->LoadFile("Window.xml");

	Item* temp = new Item();
	temp->num = 1;
	temp->name = "water";
	temp->imgFile = "water.png";
	inven["inven1"] = temp;

	temp = new Item();
	temp->num = 1;
	temp->name = "seafloor";
	temp->imgFile = "seafloor.dds";
	inven["inven2"] = temp;

	temp = new Item();
	temp->num = 1;
	temp->name = "grass";
	temp->imgFile = "grass.jpg";
	inven["inven3"] = temp;
	
	temp = new Item();
	temp->num = 1;
	temp->name = "terrain";
	temp->imgFile = "terrain.jpg";
	inven["inven4"] = temp;

	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["inven5"] = temp;

	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["inven6"] = temp;
	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["inven7"] = temp;
	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["inven8"] = temp;
	temp = new Item();
	temp->num = 0;
	temp->name = " ";
	temp->imgFile = " ";
	inven["inven9"] = temp;

	for (int i = 1; i <= 9; i++)
	{
		string t = "inven" + to_string(i);
		((UI*)Ui->Find(t))->mouseOver = [&]() {OverName = t; };
	}

	for (int i = 1; i <= 9; i++)
	{
		string t = "inven" + to_string(i);
		((UI*)Ui->Find(t))->mouseDown = [&]() {Mouse->visible = true; };
	}

	for (int i = 1; i <= 9; i++)
	{
		string t = "inven" + to_string(i);
		((UI*)Ui->Find(t))->mouseUp = [&]() {Mouse->visible = false; };
	}

	invenUpdate();

	Mouse = UI::Create("Mouse");
	Mouse->shader = Ui->shader;
	Mouse->mesh = Ui->mesh;
	Mouse->visible = false;
}

void Inven::Update()
{
	Ui->Update();
	Mouse->Update();
}

void Inven::Render()
{
	DEPTH->Set(false);
	Ui->Render();
	Mouse->Render();
	DEPTH->Set(true);
}
