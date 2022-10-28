#pragma once
class Scene1 : public Scene
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


	CubeMap* cubeMap = nullptr;
	Shader* cubeMappingShader;
	Shader* cubeMappingShader2;
	Shader* cubeMappingShader3;
	Actor*	sphere;

	RenderTarget* RT = nullptr;
	UI* PostEffect;

public:
	Scene1();
	~Scene1();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

