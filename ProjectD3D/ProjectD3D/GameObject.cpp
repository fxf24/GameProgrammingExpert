#include "framework.h"

GameObject::GameObject()
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
	visible = true;
}

void GameObject::Update()
{
	//if (not active)return;



	S = Matrix::CreateScale(scale.x, scale.y, scale.z);
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	T = Matrix::CreateTranslation(position.x, position.y, position.z);
	RT = R * T;
	W = S * RT;
	if (parent)
	{
		W *= parent->RT;
		RT *= parent->RT;
	}
	//¿Á±Õ»£√‚
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Update();
	}

}

void GameObject::Render()
{
	

}

Camera* GameObject::cam = nullptr;

void GameObject::CreateStaticMember()
{
}

void GameObject::DeleteStaticMember()
{
}
