#include "framework.h"

GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;

	rotation = 0;

	parent = nullptr;
}

void GameObject::Update()
{
	S = Matrix::CreateScale(scale.x, scale.y,1.0f);
	R = Matrix::CreateRotationZ(rotation);
	T = Matrix::CreateTranslation(position.x, position.y,0.0f);

	RT = R * T;
	W = S * RT;

	if (parent)
	{
		RT *= parent->RT;
		W *= parent->RT;
	}

	// ¿Á±Õ »£√‚
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Update();
	}
}

void GameObject::Render()
{

}
