#pragma once


class Main : public Scene
{
private:
	Camera*			Cam;
	Actor*			Map;
	Actor*			Grid;
	CubeMan*		cubeMan;
	Ray				cubeManTopRay;
	Actor*			Sphere;

	Vector3			from, to;
	float			lerpValue;
	float			time = 0.0f;

	float			Rfrom, Rto;
	float			RlerpValue;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};