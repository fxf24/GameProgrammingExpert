#pragma once
class Main : public Scene
{
private:

	Camera* Cam;

	Sky* sky;
	Terrain* Map;
	Actor* block;

	CubeMan* cubeMan;
	Ray				cubeManTopRay;

	Vector3			from, to;
	float			lerpValue;

	UI* popup;

	Actor* ObjectPool[120];
	int poolSize = -1;

	float time = 1.0f;

	float speed = 70.0f;

	int min = 0;
	int max = 0;

	bool end = false;

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
