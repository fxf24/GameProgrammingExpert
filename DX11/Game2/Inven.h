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
	__int64 money = 10000;

private:

public:
	void invenUpdate();
	void Init();
	void Update();
	void Render();
	void SetVisible() { show = true; }
};
