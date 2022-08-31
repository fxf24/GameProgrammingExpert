#pragma once


class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;

	Terrain* Map;
	Actor* Sphere;

	//상수버퍼에 갱신
	struct Brush
	{
		Vector3 point;
		float	range = 10.0f;

		float	shape;
		float	type;
		Vector2 padding;
	} brush;
	ID3D11Buffer* brushBuffer;

	//에디터에서만 존재하는 변수
	float	brushMaxHeight = 1000.0f;
	float	brushAddHeightScalr = 100.0f;
	int		brushTexture = 0;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void EditTerrain(Vector3 Pos);
};