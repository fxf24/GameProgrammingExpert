#pragma once


class Main : public Scene
{
private:
	Camera*			Cam;
	Actor*			Map;
	Actor*			Grid;
	CubeMan*		cubeMan;
	Ray				cubeManTopRay;

	Vector3			from, to;
	float			lerpValue;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};