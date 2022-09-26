#pragma once

struct Item
{
	string	name;
	string	imgFile;
	int		num;
	//int		price;
};


class Inven
{
	//그려줄객체
	UI* Ui;
	UI* Store;
	//수량 가격
	map<string,Item*> inven;

	//stirng DownName;
	string OverName;

	UI* Mouse;
	int money = 10000;

private:
	void invenUpdate();

public:
	void Init();
	void Update();
	void Render();
	void SetVisible() { Ui->visible = true; Store->visible = true; }
};

