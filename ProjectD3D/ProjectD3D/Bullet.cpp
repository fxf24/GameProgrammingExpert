#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	visible = false;
	scale.x = 50.0f;
	scalar = 0.0f;
	gravity = 0.0f;
}

void Bullet::Update()
{
	position += GetRight() * scalar * DELTA;
	position += Vector2(0, 1.0f) * DELTA * gravity;

	if (visible)
	{
		gravity += 1.0f;
		if (GetRight().x < 0)
			rotation -= DELTA * 1.0f;
		else rotation += DELTA * 1.0f;
	}

	ObLine::Update();
}

void Bullet::Shoot(Vector2 pos, Vector2 dir, float force)
{
	position = pos;
	rotation = atan2f(dir.y, dir.x);
	scalar = force;
	visible = true;
}
