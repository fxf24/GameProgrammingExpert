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
public:
	bool show = false;
	//�׷��ٰ�ü
	UI* Ui;
	UI* Store;
	//���� ����
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
	void SetVisible() { show = true; }
};

