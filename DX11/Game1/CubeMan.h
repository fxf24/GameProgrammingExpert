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
	float		gravity;
	Vector3     lastPos;
	Vector3		movingPosition;
	Vector3		dir;
private:
	void Idle();
	void Walk();
public:
	bool		jumping;
	bool		isLerping;
	CubeMan();
	void Update();
	void WorldUpdate();
	bool GetJumpping() { return jumping;}
	Vector3 GetLastPos() { return lastPos;}
	void Falling();
	void Landing();
	void SetMovingPosition(Vector3 position);
};

