#pragma once


class Main : public Scene
{
private:
	Camera*			Cam;
	Actor*			Grid;
	vector<Actor*>	List;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	Matrix ToMatrix(aiMatrix4x4& value)
	{
		return Matrix
		(
			value.a1, value.b1, value.c1, value.d1,
			value.a2, value.b2, value.c2, value.d2,
			value.a3, value.b3, value.c3, value.d3,
			value.a4, value.b4, value.c4, value.d4
		);
	};
	void ReadNode(GameObject* dest, aiNode* src);
};