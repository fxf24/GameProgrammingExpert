#pragma once
class Animation
{
public:
	UINT					frameMax;
	UINT					boneMax;
	Matrix**				arrFrameBone;//	ÇÁ·¹ÀÓ°¹¼ö* º»°¹¼ö
	float					tickPerSecond;
	string					file;


	Animation();
	~Animation();
	void LoadFile(string file);
	void SaveFile(string file);
};
enum class AnimationState
{
	LOOP,
	ONCE,
	STOP//Pause
};

class Animations
{
	struct Animator
	{
		float frameWeight = 0.0f;
		UINT  currentFrame = 0;
		UINT  nextFrame = 1;
		UINT  animIdx = 0;
		AnimationState animState = AnimationState::STOP;
	};
	void AnimatorUpdate(Animator& Animator);
public:
	void Update();
	Animator							currentAnimator;
	//Animator							nextAnimator;
	vector<shared_ptr<Animation>>		playList;
	Matrix	GetFrameBone(int boneIndex);
	void	PlayAnimation(AnimationState state, UINT idx);
	void	RenderDetail();
};