#pragma once

// ���ο��� ���� ����

class Main : public Scene
{
private:
	class Scene* sc1;
	thread*		  t1;

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