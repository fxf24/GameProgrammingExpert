#pragma once

class Scene1 : public Scene
{
private:
	Camera* Cam;

	Sky* sky;
	Actor* Player;
	Terrain* Map;
	Actor* cube1;
	Actor* cube2;
	

	Shadow*			shadow;
	Environment*	cubeMap1;
	Environment*	cubeMap2;
	PostEffect*		postEffect = nullptr;

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

