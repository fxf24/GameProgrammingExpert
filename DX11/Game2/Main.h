#pragma once
class Main : public Scene
{
private:

	Camera* Cam;
	Actor* Grid;

	UI* UI;
	Vector3 PrevMouse;

	bool max = false;
	string from = "";
	string to = "";
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void Resize();
	void ClickEvent();
	void UpEvent();
};
