#include "stdafx.h"

CubeMan::CubeMan()
{
	LoadFile("CubeMan.xml");
	state = PlayerState::IDLE;
	shaketime = 0.0f;
	mul = 1.0f;
}

void CubeMan::Update()
{
	shaketime += DELTA;
	if (shaketime > 0.25f)
	{
		mul *= -1.0f;
		shaketime -= 0.5f;
	}
	switch (state)
	{
	case PlayerState::IDLE:
		Idle();
		break;
	case PlayerState::WALK:
		Walk();
		break;
	}

	if (INPUT->KeyPress(VK_LEFT))
	{
		rotation.y -= DELTA;
	}
	if (INPUT->KeyPress(VK_RIGHT))
	{
		rotation.y += DELTA;
	}
	
	GameObject::Update();
}

void CubeMan::Idle()
{
	Find("Neck")->rotation.y += mul * DELTA;

	//idle to walk
	if (INPUT->KeyDown(VK_UP))
	{
		state = PlayerState::WALK;
		shaketime = 0.25f;
	}
}

void CubeMan::Walk()
{
	position += GetForward() * 10.0f * DELTA;
	Find("Neck")->rotation.y = 0.0f;

	
	if (INPUT->KeyUp(VK_UP))
	{
		state = PlayerState::IDLE;
		shaketime = 0.25f;
	}
}