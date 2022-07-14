#pragma once


class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;
	vector<Actor*> List;

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