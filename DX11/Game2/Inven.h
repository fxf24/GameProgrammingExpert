#pragma once

struct Item
{
	string	name;
	string	imgFile;
	int		num;
	//GameObject* temp;
	//int		price;
};


class Inven
{
public:
	bool show = true;
	//�׷��ٰ�ü
	UI* Ui;
	//���� ����
	map<string,Item*> inven;
	//map<string,Item*> shop;

	string	OverName;
	UI*		Mouse;
	__int64 Gold = 10000;

private:
	void invenUpdate();

public:
	void Init();
	void Update();
	void Render();
};

