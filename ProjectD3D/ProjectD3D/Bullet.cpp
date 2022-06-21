#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	visible = false;
	scale.x = 50.0f;
	scalar = 0.0f;
}

void Bullet::Update()
{
	Vector2 Velocity = dir * scalar + Vector2(0, 1.0f) * gravity;
	position += Velocity * DELTA;

	rotation = atan2f(Velocity.y, Velocity.x);

	gravity += 1000.0f * DELTA;
	
	ObLine::Update();
}

void Bullet::Shoot(Vector2 pos, Vector2 dir, float force)
{
	position = pos;
	this->dir = dir;
	scalar = force;
	visible = true;
	gravity = 0.0f;
}
