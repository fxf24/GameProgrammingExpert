#pragma once
class Main : public Scene
{
private:

	Camera* Cam;

	Sky* sky;
	Actor* Grid;
	Actor* _Shop;
	Actor* Map;

	//UI* Ui;
	Vector3 PrevMouse;
	Inven   inv;
	Shop	shop;
	float	bgmscale = 1.0f;
	float	Gunscale = 1.0f;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	//void Resize();

};
