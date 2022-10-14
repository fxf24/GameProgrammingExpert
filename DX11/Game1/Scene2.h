#pragma once

<<<<<<< HEAD
#define ARRAY_SIZE 30
=======
#define ARRAY_SIZE 10
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b

class Scene2 : public Scene
{
private:
	Camera* Cam;
	Camera* Cam2;
	Actor* Grid;
<<<<<<< HEAD

	Actor* Sphere[ARRAY_SIZE][ARRAY_SIZE][ARRAY_SIZE];

	vector<Actor*> RenderList;

=======

	Actor* Sphere[ARRAY_SIZE][ARRAY_SIZE][ARRAY_SIZE];
	vector<Actor*> RenderList;
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
public:
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

};

