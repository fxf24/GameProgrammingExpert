#pragma once
class Main : public Scene
{
private:

	Camera* Cam;

	Sky*	sky;
	Actor* Grid;
	Actor* Player;
	Light* Point;
	Light* Point2;
	Terrain* Map;

	Int2   Pos;

	Actor* Sphere[3][3];

	RenderTarget*	RT = nullptr;
	UI*				PostEffect;

	struct Blur
	{
		int count;
		float width;
		float height;
		int select;
		Color blendColor = Color(0.5f,0.5f, 0.5f, 0.5f);
		Vector2  center;
		float   radius = 2000.0f;
		float   padding;
	} blur;
	ID3D11Buffer* blurBuffer;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	//void Resize();

};