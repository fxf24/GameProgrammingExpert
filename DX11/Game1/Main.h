#pragma once

// 메인에는 씬만 구성

class Main : public Scene
{
private:
	class Scene* sc1;
	thread*		  t1;

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