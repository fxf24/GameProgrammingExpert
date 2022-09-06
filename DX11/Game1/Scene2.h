#pragma once
class Scene2 : public Scene
{
private:
	Camera* Cam;
	Terrain* Map;
	Actor* Grid;
	CubeMan* cubeMan;
	Ray				cubeManTopRay;

	Vector3			from, to;
	float			lerpValue;

	float			Rfrom, Rto;
	float			RlerpValue;
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

