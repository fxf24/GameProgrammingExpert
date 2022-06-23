#pragma once
class GameObject
{
public:
	bool				visible;
	static class Camera* cam;

	Vector3				position;
	Vector3				scale;
	Vector3				rotation;
	GameObject*			parent;
	vector<GameObject*> children;

	Matrix		S, R, T, RT, W;
	GameObject();
	virtual ~GameObject() {};

	virtual void Update();
	virtual void Render();

	static void CreateStaticMember();
	static void DeleteStaticMember();

	Vector3 GetRight() { return Vector3(RT._11, RT._12,RT._13); }
	Vector3 GetUp() { return Vector3(RT._21, RT._22, RT._23); }
	Vector3 GetForward() { return Vector3(RT._31, RT._32, RT._33); }
};

