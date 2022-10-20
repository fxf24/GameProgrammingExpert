#pragma once
class Main : public Scene
{
private:

	Camera* Cam;
	CubeMan* cubeMan;

	Sky* sky;
	Terrain* Map;

	Actor* Wall[20];

	UI* popup;

	int score = -10;
	float time = 3.0f;
	float speed = 30.0f;
	bool fail = false;
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
