#pragma once


class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;

	Terrain* Map;
	Actor* Sphere;
	//�����Ϳ����� �����ϴ� ����
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
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void EditTerrain(Vector3 Pos);
};