#pragma once

#define ARRAY_SIZE 30

class Scene2 : public Scene
{
private:
	Camera* Cam;
	Camera* Cam2;
	Actor* Grid;

	Actor* Sphere[ARRAY_SIZE][ARRAY_SIZE][ARRAY_SIZE];

	vector<Actor*> RenderList;

public:
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

};

