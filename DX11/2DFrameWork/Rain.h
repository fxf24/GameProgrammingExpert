#pragma once
struct RAIN_DESC
{
	Vector3 velocity;
	float padding;

	Vector3 range;
	float time;
	RAIN_DESC()
	{
		velocity = Vector3(0, -1, 0);
		range = Vector3(500, 500, 500);
		time = 0.0;
	}
};

class Particle
{
protected:
	// �� ����ð�
	float duration = 1.0f;
	// ���� ������� �ð�
	float playTime = 0.0f;
	// ������ΰ�
	bool isPlaying = false;
public:
	virtual void Play()
	{
		playTime = 0.0f;
		isPlaying = true;
	};
	virtual void Stop()
	{
		isPlaying = false;
	};
	void		 Gui();
	void		 UpdateParticle();
	bool		 IsPlaying() { return isPlaying; } // ������ΰ�
	float		 PlayTime() { return playTime / duration; } // ����ð� ����
};

class Rain : public Actor, public Particle
{
	static ID3D11Buffer* RainBuffer;

public:
	RAIN_DESC desc;
	Vector2 particleScale;
	int particleCount;

	static void CreateStaticMember();
	static void DeleteStaticMember();
	static Rain* Create(string name = "Rain");
	virtual void Render();
	virtual void Update();
	void RenderDetail();
	void Reset();
	virtual void Play();
	virtual void Stop();
};

