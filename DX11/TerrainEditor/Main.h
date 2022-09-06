#pragma once


class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;

	Terrain* Map;
	Actor* Sphere;
	deque<Vector3> Way;

	float MoveValue;
	Vector3 P1, P2;
	float Dis;

	//������ۿ� ����
	struct Brush
	{
		Vector3 point;
		float	range = 10.0f;

		float	shape;
		float	type;
		Vector2 padding;
	} brush;
	ID3D11Buffer* brushBuffer;

	//�����Ϳ����� �����ϴ� ����
	float	brushMaxHeight = 1000.0f;
	float	brushAddHeightScalr = 100.0f;
	int		brushTexture = 0;
	int		nodeEdit = 0;
	int     prevPick = -1;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void EditTerrain(Vector3 Pos);
};