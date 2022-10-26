#pragma once
class Scene2 : public Scene
{
	Camera* Cam;

	Sky* sky;
	Actor* Grid;
	Actor* Player;
	Light* Point;
	Light* Point2;
	Terrain* Map;

	Int2   Pos;

	Actor* Sphere[3][3];

	RenderTarget* RT = nullptr;
	UI* PostEffect;
public:
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

};

