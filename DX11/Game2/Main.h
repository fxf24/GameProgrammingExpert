#pragma once
class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;

	Actor* sp1;
	Actor* sp2;
	float lerpValue;
	Vector3 Point[4];

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
