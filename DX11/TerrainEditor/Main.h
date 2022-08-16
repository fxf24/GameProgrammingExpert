#pragma once


class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;

	Actor* Map;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
	void UpdateTerrainNormal();
};