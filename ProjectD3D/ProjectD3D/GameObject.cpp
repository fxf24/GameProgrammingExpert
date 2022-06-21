#include "framework.h"

GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;

	rotation = 0;

	parent = nullptr;
	visible = true;
}

void GameObject::Update()
{
	//if (not active) return;


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
	//if (not active) return;


	//Right
	axis->scale.x = scale.x;

	Vector2 Right = GetRight();
	axis->rotation = atan2f(Right.y, Right.x);
	axis->position = Vector2(W._41, W._42);
	axis->Update();
	axis->Render();

	endPoint = axis->GetEndPoint();

	//Down
	axis->scale.x = scale.y;

	Vector2 Down = GetDown();
	axis->rotation = atan2f(Down.y, Down.x);
	axis->Update();
	axis->Render();
}

ObLine* GameObject::axis = nullptr;

void GameObject::CreateStaticMember()
{
	axis = new ObLine();
}

void GameObject::DeleteStaticMember()
{
	delete axis;
}
