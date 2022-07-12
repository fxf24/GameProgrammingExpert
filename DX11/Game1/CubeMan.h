#pragma once

enum class PlayerState
{
	IDLE,
	WALK
};

class CubeMan: public Actor
{
private:
	PlayerState state;
	float		shaketime;
	float		mul;
	float		gravity;
	bool		jumping;

private:
	void Idle();
	void Walk();
public:
	CubeMan();
	void Update();
	bool GetJumpping() { return jumping;}
};

