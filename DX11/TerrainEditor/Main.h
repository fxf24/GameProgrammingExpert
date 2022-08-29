#pragma once


class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;

	Terrain* Map;
	Actor* Sphere;
	//에디터에서만 존재하는 변수
	float brushMaxHeight = 1000.0f;
	float brushAddHeightScalr = 100.0f;
	float brushRange = 10.0f;
	int   brushTexture = 0;

	bool rect = true;
	float number = 1.0f;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void EditTerrain(Vector3 Pos);
};