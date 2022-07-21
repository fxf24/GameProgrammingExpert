#include "stdafx.h"

CubeMan::CubeMan()
{
	LoadFile("Character2.xml");
	state = PlayerState::IDLE;
	shaketime = 0.0f;
	mul = 1.0f;
	surface = 0.0f;
	jumping = false;
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
		Walk(1);
		break;
	case PlayerState::BACKWALK:
		Walk(-1);
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
	if (INPUT->KeyDown(VK_SPACE) and not jumping)
	{
		jumping = true;
		gravity = -60.0f;
	}

	
	if (jumping)
	{
		MoveWorldPos(-UP * gravity * DELTA);
		gravity += 120.0f * DELTA;
		if (surface > GetWorldPos().y)
		{
			jumping = false;
			SetWorldPosY(surface + 0.2f);
		}
	}
	else if (GetWorldPos().y - surface > 0.4f)
	{
		gravity = 30.0f;
		MoveWorldPos(-UP * gravity * DELTA);
	}

	GameObject::Update();
}

void CubeMan::Idle()
{
	//°í°³Á£±â,Â÷·ÇÀÚ¼¼À¯Áö
	Find("Head")->rotation.y += mul * DELTA;

	//idle to walk
	if (INPUT->KeyDown(VK_UP))
	{
		state = PlayerState::WALK;
		shaketime = 0.0f;
	}
	if (INPUT->KeyDown(VK_DOWN))
	{
		state = PlayerState::BACKWALK;
		shaketime = 0.0f;
	}
}

void CubeMan::Walk(float dir)
{
	prePosition = position;
	position += dir * GetForward() * 20.0f * DELTA;
	//ÆÈ´Ù¸®ÈÖÁ£±â,°í°³°íÁ¤
	Find("Head")->rotation.y = 0.0f;

	//walk to idle
	if (INPUT->KeyUp(VK_UP))
	{
		state = PlayerState::IDLE;
		shaketime = 0.0f;
	}
	if (INPUT->KeyUp(VK_DOWN))
	{
		state = PlayerState::IDLE;
		shaketime = 0.0f;
	}
}
