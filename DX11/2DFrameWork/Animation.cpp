#include "framework.h"

Animation::Animation()
{
	frameMax = 0;
	boneMax = 0;
	tickPerSecond = 0;
	arrFrameBone = nullptr;
	file = "";
}

Animation::~Animation()
{
	for (UINT i = 0; i < frameMax; i++)
	{
		delete[] arrFrameBone[i];
	}
	delete[] arrFrameBone;
}


void Animation::LoadFile(string file)
{
	this->file = file;
	BinaryReader in;
	wstring path = L"../Contents/Animation/" + Util::ToWString(file);
	in.Open(path);

	frameMax = in.Int();
	boneMax = in.Int();
	tickPerSecond = in.Float();

	arrFrameBone = new Matrix * [frameMax];
	for (UINT i = 0; i < frameMax; i++)
	{
		arrFrameBone[i] = new Matrix[boneMax];
	}

	for (UINT i = 0; i < frameMax; i++)
	{
		for (UINT j = 0; j < boneMax; j++)
		{
			arrFrameBone[i][j] = in.matrix();
		}
	}
	in.Close();
}

void Animation::SaveFile(string file)
{
	this->file = file;
	BinaryWriter out;
	wstring path = L"../Contents/Animation/" + Util::ToWString(file);
	out.Open(path);

	out.Int(frameMax);
	out.Int(boneMax);
	out.Float(tickPerSecond);

	for (UINT i = 0; i < frameMax; i++)
	{
		for (UINT j = 0; j < boneMax; j++)
		{
			out.matrix(arrFrameBone[i][j]);
		}
	}
	out.Close();
}

void Animations::AnimatorUpdate(Animator& Animator)
{
	if (Animator.animState == AnimationState::LOOP)
	{
		Animator.frameWeight += DELTA * playList[Animator.animIdx]->tickPerSecond;
		if (Animator.frameWeight >= 1.0f)
		{
			Animator.frameWeight = 0.0f;
			Animator.currentFrame++;
			Animator.nextFrame++;
			if (Animator.nextFrame >= playList[Animator.animIdx]->frameMax)
			{
				Animator.currentFrame = 0;
				Animator.nextFrame = 1;
			}
		}
	}
	else if (Animator.animState == AnimationState::ONCE)
	{
		Animator.frameWeight += DELTA * playList[Animator.animIdx]->tickPerSecond;
		if (Animator.frameWeight >= 1.0f)
		{
			Animator.frameWeight = 0.0f;
			Animator.currentFrame++;
			Animator.nextFrame++;
			if (Animator.nextFrame >= playList[Animator.animIdx]->frameMax)
			{
				Animator.currentFrame = 0;
				Animator.nextFrame = 1;
				Animator.animState = AnimationState::STOP;
			}
		}
	}
}

void Animations::Update()
{
	AnimatorUpdate(currentAnimator);
}

Matrix Animations::GetFrameBone(int boneIndex)
{
	return playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.nextFrame][boneIndex]
		* currentAnimator.frameWeight +
		playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.currentFrame][boneIndex]
		* (1.0f - currentAnimator.frameWeight);
}

void Animations::PlayAnimation(AnimationState state, UINT idx)
{
	currentAnimator.animState = state;
	currentAnimator.animIdx = idx;
}

void Animations::RenderDetail()
{
	for (UINT i = 0; i < playList.size(); i++)
	{
		string name = to_string(i) + playList[i]->file;
		string button = name + "Stop";
		if (ImGui::Button(button.c_str()))
		{
			PlayAnimation(AnimationState::STOP, i);
		}
		ImGui::SameLine();
		button = name + "Once";
		if (ImGui::Button(button.c_str()))
		{
			PlayAnimation(AnimationState::ONCE, i);
		}
		ImGui::SameLine();
		button = name + "Loop";
		if (ImGui::Button(button.c_str()))
		{
			PlayAnimation(AnimationState::LOOP, i);
		}
	}
}
