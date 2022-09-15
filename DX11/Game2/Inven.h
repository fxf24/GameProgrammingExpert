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
	//수량 가격
	map<string,Item*> inven;

	//stirng DownName;
	string OverName;

	UI* Mouse;


private:
	void invenUpdate();

public:
	void Init();
	void Update();
	void Render();
};

