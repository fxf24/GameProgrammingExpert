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
	//�׷��ٰ�ü
	UI* Ui;
	//���� ����
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

