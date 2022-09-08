#pragma once
class Main : public Scene
{
private:

	Camera* Cam;
	Actor* Grid;

	Actor* UI;
	Vector3 PrevMouse;

	bool max = false;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
