#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	visible = false;
	scale.x = 50.0f;
}

void Bullet::Update()
{
	position += GetRight() * scalar * DELTA;
	ObLine::Update();
}

void Bullet::Shoot(Vector2 pos, Vector2 dir, float force)
{
	position = pos;
	rotation = atan2f(dir.y, dir.x);
	scalar = force;
	visible = true;
}
