#pragma once
class Main : public Scene
{
private:

	Camera* Cam;

	Sky* sky;
	Terrain* Map;

	Actor* hammer;
	Actor* moles[9];

	int score = 0;
	int order[120];
	float moleDuration[9];
	int od = 0;
	float time = 1.0f;
	float speed = 50.0f;

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
