#include "stdafx.h"

CubeMan::CubeMan()
{
	LoadFile("Model.xml");
	state = PlayerState::IDLE;
	jumping = false;
	movingPosition = position;
	isLerping = false;
}

void CubeMan::Update()
{
	//�����̱� ���� ��ġ��
	lastPos = GetWorldPos();


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
		/*if (gravity > 30.0f)
		{
			jumping = false;
		}*/
	}

	if (isLerping)
	{
		position += dir * 10 * DELTA;

		float dis = Vector3::Distance(position, movingPosition);

		if (dis <= 1.0f)
		{
			isLerping = false;
			anim->PlayAnimation(AnimationState::LOOP, 0);
		}
	}

	Actor::Update();
}

void CubeMan::WorldUpdate()
{
	Transform::Update();
}

void CubeMan::Falling()
{
	if (jumping) return;
	jumping = true;
	gravity = 0.0f;
}

void CubeMan::Landing()
{
	if (not jumping) return;
	jumping = false;
	gravity = 0.0f;
}

void CubeMan::SetMovingPosition(Vector3 pos)
{
	movingPosition = pos;
	dir = movingPosition - position;

	Vector2 mp = Vector2(dir.x, dir.z);
	Vector2 p = Vector2(GetForward().x, GetForward().z);

	float r = acos(p.Dot(mp) / p.Length() / mp.Length()) * PI;
	if (r > PI)
	{
		r -= PI;
		r = -r;
	}

	rotation.y += r;
	anim->PlayAnimation(AnimationState::LOOP, 1);
	dir.Normalize();
}

void CubeMan::Idle()
{
	//������,�����ڼ�����
	//Find("Head")->rotation.y += mul * DELTA;

	//idle to walk
	if (INPUT->KeyPress(VK_UP) or INPUT->KeyPress(VK_DOWN))
	{
		state = PlayerState::WALK;
		anim->PlayAnimation(AnimationState::LOOP, 1);
	}
}

void CubeMan::Walk()
{
	if (INPUT->KeyPress(VK_UP))
	{
		position -= GetForward() * 10.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		position += GetForward() * 10.0f * DELTA;
	}
	//�ȴٸ�������,������
	//Find("Head")->rotation.y = 0.0f;

	//walk to idle
	if (INPUT->KeyPress(VK_UP) == false and INPUT->KeyPress(VK_DOWN) == false)
	{
		state = PlayerState::IDLE;
		anim->PlayAnimation(AnimationState::LOOP, 0);
	}
}
