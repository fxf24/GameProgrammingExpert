#pragma once

enum class PlayerState
{
	IDLE,
	WALK,
	BACKWALK
};

class CubeMan: public Actor
{
private:
	Vector3		prePosition;
	PlayerState state;
	float		shaketime;
	float		mul;
	float		gravity;
	float		surface;
	bool		jumping;

private:
	void Idle();
	void Walk(float dir);
public:
	CubeMan();
	void Update();
	bool GetJumpping() { return jumping;}
	void SetSurface(float y) { surface = y; }
	Vector3 GetPrePosition() { return prePosition; }
};

