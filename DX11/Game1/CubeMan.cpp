#include "stdafx.h"

CubeMan::CubeMan()
{
	LoadFile("New_Character.xml");
	state = PlayerState::IDLE;
	shaketime = 0.0f;
	mul = 1.0f;
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
	if (INPUT->KeyDown(VK_SPACE)and not jumping)
	{
		jumping = true;
		gravity = -30.0f;
	}

	if (jumping)
	{
		MoveWorldPos(-UP * gravity * DELTA);
		gravity += 30.0f * DELTA;
		if (gravity > 30.0f)
		{
			jumping = false;
		}
	}

	GameObject::Update();
}

void CubeMan::Idle()
{
	//°í°³Á£±â,Â÷·ÇÀÚ¼¼À¯Áö
	Find("Head")->rotation.y += mul * DELTA;

	Find("LeftPelvisMuscle")->rotation.x = 0.0f;
	Find("RightPelvisMuscle")->rotation.x = 0.0f;
	Find("LeftDeltoidMuscle")->rotation.x = 0.0f;
	Find("RightDeltoidMuscle")->rotation.x = 0.0f;
	//idle to walk
	if (INPUT->KeyDown(VK_UP))
	{
		state = PlayerState::WALK;
		shaketime = 0.0f;
	}
}

void CubeMan::Walk()
{
	position += GetForward() * 10.0f * DELTA;
	//ÆÈ´Ù¸®ÈÖÁ£±â,°í°³°íÁ¤
	Find("Head")->rotation.y = 0.0f;

	Find("LeftPelvisMuscle")->rotation.x -= mul * DELTA;
	Find("RightPelvisMuscle")->rotation.x += mul * DELTA;
	Find("LeftDeltoidMuscle")->rotation.x -= mul * DELTA;
	Find("RightDeltoidMuscle")->rotation.x += mul * DELTA;
	//walk to idle
	if (INPUT->KeyUp(VK_UP))
	{
		state = PlayerState::IDLE;
		shaketime = 0.0f;
	}
}
