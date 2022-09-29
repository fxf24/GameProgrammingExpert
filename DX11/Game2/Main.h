#pragma once
class Main : public Scene
{
private:

	Camera* Cam;
	Actor* Grid;
	Actor* _Shop;

	//UI* Ui;
	Vector3 PrevMouse;
	Inven   inv;
	Shop	store;
	float bgmscale = 1.0f;
	float goldscale = 1.0f;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	//void Resize();

};
