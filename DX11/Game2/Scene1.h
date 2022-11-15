#pragma once
class Scene1 : public Scene
{
private:
	Camera* Cam;
	Camera* Cam2;

	Sky* sky;
	Actor* Player;
	Terrain* Map;

	RenderTarget* RT = nullptr;
	ID3D11ShaderResourceView* srv;

public:
	Scene1();
	~Scene1();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

