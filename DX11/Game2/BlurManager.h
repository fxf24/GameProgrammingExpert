#pragma once

struct Blur
{
	int count;
	float width;
	float height;
	int select;
	Color blendColor = Color(0.5f, 0.5f, 0.5f, 1.0f);
	Vector2  center;
	float   radius = 2000.0f;
	float   padding;
};

class BlurManager : public Singleton<BlurManager>
{
public:
	BlurManager();
	~BlurManager();
	Blur blur;
	ID3D11Buffer* blurBuffer;
	void Update();
	void Set();
};

