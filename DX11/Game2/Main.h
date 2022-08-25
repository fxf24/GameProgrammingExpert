#pragma once
class Main : public Scene
{
private:

	Camera* Cam;
	Actor* Grid;
	Actor* Sp1;

	Actor* Sp2;
	Vector3 Point[4];
	float	lerpValue;

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
