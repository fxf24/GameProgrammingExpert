#pragma once
class Scene2 : public Scene
{
private:
	Camera* Cam;

	Sky* sky;
	Actor* Grid;
	Actor* Player;
	Light* Point;
	Light* Point2;
	Terrain* Map;

	Int2   Pos;


	RenderTarget* RT = nullptr;
	UI* PostEffect;

public:
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};