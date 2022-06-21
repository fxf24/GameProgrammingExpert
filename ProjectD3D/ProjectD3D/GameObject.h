#pragma once
class GameObject
{
public:
	//bool				active;
	bool				visible;
	static class ObLine* axis;

	Vector2				position;
	Vector2				scale;
	Vector2				endPoint;
	float				rotation;
	GameObject*			parent;
	vector<GameObject*> children;

	Matrix		S, R, T, RT, W;
	GameObject();
	virtual ~GameObject() {};

	virtual void Update();
	virtual void Render();

	static void CreateStaticMember();
	static void DeleteStaticMember();

	Vector2 GetRight() { return Vector2(RT._11, RT._12); }
	Vector2 GetDown() { return Vector2(RT._21, RT._22); }
};

