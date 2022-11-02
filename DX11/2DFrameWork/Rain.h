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

class Rain : public Actor
{
	static ID3D11Buffer* RainBuffer;
	RAIN_DESC desc;

public:
	static void CreateStaticMember();
	static void DeleteStaticMember();
	static Rain* Create(string name = "Rain");
	virtual void Render();
};

