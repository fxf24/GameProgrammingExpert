#pragma once
class LoadingScene : public Scene
{
private:
	Camera* Cam;
	Actor* Sphere;
	Actor* Grid;
	
	thread* t1;
	int		LoadingMaxCount;
	string  targetName;


public:
	LoadingScene();
	~LoadingScene();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
	void LoadingTarget(string name,int loadingMaxCount, void(*FcnPtr)());
};


