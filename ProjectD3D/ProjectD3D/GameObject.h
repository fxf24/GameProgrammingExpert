#pragma once
class GameObject
{
public:
	Vector2				position;
	Vector2				scale;
	float				rotation;
	GameObject*			parent;
	vector<GameObject*> children;

	Matrix		S, R, T, RT, W;
	GameObject();
	virtual ~GameObject() {};

	virtual void Update();
	virtual void Render();



};

