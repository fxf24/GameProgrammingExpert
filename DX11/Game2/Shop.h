#pragma once
class Shop
{

public:
	bool show = true;
	//�׷��ٰ�ü
	UI* Ui;
	map<string, Item*> inven;
	Inven* pInven;

private:
	void invenUpdate();

public:
	void Init(Inven* pInven);
	void Update();
	void Render();
};
