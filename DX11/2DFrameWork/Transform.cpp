#include "framework.h"
bool Transform::worldPos = false;

Transform::Transform()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	parent = nullptr;
}

void Transform::Update()
{
	S = Matrix::CreateScale(scale.x, scale.y, scale.z);
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	T = Matrix::CreateTranslation(position.x, position.y, position.z);
	RT = R * T;
	W = S * RT;
	if (parent)
	{
		S *= parent->S;
		RT *= parent->RT;
		W *= parent->W;
	}
}


Vector3 Transform::GetWorldPos()
{
	return Vector3(W._41, W._42, W._43);
}

void Transform::SetWorldPos(Vector3 WPos)
{
	if (parent)
		position = Vector3::Transform(WPos, parent->W.Invert());
	else
		position = WPos;
}

void Transform::SetWorldPosX(float WPosX)
{
	if (parent)
		position.x = Vector3::Transform(Vector3(WPosX, W._42, W._43), parent->W.Invert()).x;
	else
		position.x = WPosX;
}

void Transform::SetWorldPosY(float WPosY)
{
	if (parent)
		position.y = Vector3::Transform(Vector3(W._41, WPosY, W._43), parent->W.Invert()).y;
	else
		position.y = WPosY;
}

void Transform::SetWorldPosZ(float WPosZ)
{
	if (parent)
		position.z = Vector3::Transform(Vector3(W._41, W._42, WPosZ), parent->W.Invert()).z;
	else
		position.z = WPosZ;
}

void Transform::MoveWorldPos(const Vector3& WScaleVec)
{
	if (parent)
		position += Vector3::TransformNormal(WScaleVec, parent->W.Invert());
	else
		position += WScaleVec;
}

Vector3 Transform::GetLocalPos()
{
	if (parent)
		return Vector3::Transform(position, parent->S);
	else
		return position;
}

void Transform::SetLocalPos(Vector3 WPos)
{
	if (parent)
		position = Vector3::Transform(WPos, parent->S.Invert());
	else
		position = WPos;
}

void Transform::SetLocalPosX(float WPosX)
{
	if (parent)
		position.x = WPosX / parent->S._11;
	else
		position.x = WPosX;
}

void Transform::SetLocalPosY(float WPosY)
{
	if (parent)
		position.y = WPosY / parent->S._22;
	else
		position.y = WPosY;
}

void Transform::SetLocalPosZ(float WPosZ)
{
	if (parent)
		position.z = WPosZ / parent->S._33;
	else
		position.z = WPosZ;
}

void Transform::MoveLocalPos(const Vector3& WScaleVec)
{
	if (parent)
	{
		Matrix InverseS;
		InverseS._11 = 1.0f / parent->S._11;
		InverseS._22 = 1.0f / parent->S._22;
		InverseS._33 = 1.0f / parent->S._33;
		Vector3 LScaleVec = Vector3::Transform(WScaleVec, InverseS);
		position += LScaleVec;
	}
	else
		position += WScaleVec;
}
