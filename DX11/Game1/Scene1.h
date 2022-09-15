#pragma once
class Scene1 : public Scene
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
	Scene1();
	~Scene1();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

};

