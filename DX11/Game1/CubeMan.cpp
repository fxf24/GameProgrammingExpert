#include "stdafx.h"

CubeMan::CubeMan()
{
	LoadFile("Character2.xml");
	state = PlayerState::IDLE;
	shaketime = 0.0f;
	mul = 1.0f;
	jumping = false;
}

void CubeMan::Update()
{
	//움직이기 전의 위치값
	lastPos = position;

	shaketime += DELTA;
	if (shaketime > 0.5f)
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

void CubeMan::WorldUpdate()
{
	Transform::Update();
}

void CubeMan::Falling()
{
	jumping = true;
	gravity = 0.0f;
}

void CubeMan::Idle()
{
	//고개젓기,차렷자세유지
	Find("Head")->rotation.y += mul * DELTA;

	//idle to walk
	if (INPUT->KeyPress(VK_UP) or INPUT->KeyPress(VK_DOWN))
	{
		state = PlayerState::WALK;
		shaketime = 0.0f;
	}
}

void CubeMan::Walk()
{
	if (INPUT->KeyPress(VK_UP))
	{
		position += GetForward() * 20.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		position -= GetForward() * 20.0f * DELTA;
	}
	//팔다리휘젓기,고개고정
	Find("Head")->rotation.y = 0.0f;

	//walk to idle
	if (INPUT->KeyPress(VK_UP) == false and INPUT->KeyPress(VK_DOWN) == false)
	{
		state = PlayerState::IDLE;
		shaketime = 0.25f;
	}
}
