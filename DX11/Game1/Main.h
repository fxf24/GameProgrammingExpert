#pragma once


class Main : public Scene
{
private:
	Camera*		Cam;
	
	ObRect		Sun;
	ObRect		SunBone[4];
	ObRect		Planet[5];
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