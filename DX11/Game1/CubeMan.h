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
	Vector3     lastPos;
	float		surface;

private:
	void Idle();
	void Walk();
public:
	CubeMan();
	void Update();
	void WorldUpdate();
	bool GetJumpping() { return jumping;}
	Vector3 GetLastPos() { return lastPos;}
	void Falling();
	void SetSurface(float y) { surface = y; }
};

