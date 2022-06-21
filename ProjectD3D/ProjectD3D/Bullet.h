#pragma once

class Bullet : public ObLine
{

public:
	float scalar;
	float gravity;
	Vector2 dir;

	Bullet();
	void Update() override;
	void Shoot(Vector2 pos, Vector2 dir, float force);
};
