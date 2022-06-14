#pragma once
class GameObject
{
public:
	Vector2		position;
	Vector2		scale;
	float		rotation;

	Matrix		S, R, T, W;
	GameObject();
	virtual ~GameObject() {};

	virtual void Update();
	virtual void Render();



};

