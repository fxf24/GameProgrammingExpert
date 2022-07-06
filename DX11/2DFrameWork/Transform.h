#pragma once
class Transform
{
public:
	Matrix				S, R, T, RT, W;
	bool				visible;
	Vector3				position;
	Vector3				scale;
	Vector3				rotation;
public:
	Transform();
	virtual ~Transform() {};
	void Update(class GameObject* parent);
public:
	Vector3 GetRight() { return Vector3(RT._11, RT._12, RT._13); }
	Vector3 GetUp() { return Vector3(RT._21, RT._22, RT._23); }
	Vector3 GetForward() { return Vector3(RT._31, RT._32, RT._33); }
};

