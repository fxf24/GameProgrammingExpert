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
	UI* Ui;
	map<string, Item*> inven;

	string OverName;
	UI* Mouse;
private:
	void invenUpdate();

public:
	void Init();
	void Update();
	void Render();
};

