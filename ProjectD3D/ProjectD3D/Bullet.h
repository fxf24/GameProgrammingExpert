#pragma once

class Bullet : public ObLine
{

public:
	float scalar;
	float gravity;

	Bullet();
	void Update() override;
	void Shoot(Vector2 pos, Vector2 dir, float force);
};
