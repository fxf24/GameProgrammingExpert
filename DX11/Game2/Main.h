#pragma once
class Main : public Scene
{
private:

	Camera* Cam;

	Sky*	sky;
	Actor* Grid;
	Actor* Player;
	Actor* Map;
	Light* Point;
	Light* Point2;

	Actor* hammer;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	//void Resize();

};
