#pragma once


class Main : public Scene
{
private:
	Camera*			Cam[4];
	GameObject		Sun;
	GameObject		SunBone[5];
	GameObject		Planet[5];
	bool checkbox = true;
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