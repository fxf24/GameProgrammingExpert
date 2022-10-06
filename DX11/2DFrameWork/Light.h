#pragma once
struct DirLight
{
	Vector4			direction;
	Color			color;
	DirLight()
	{
		direction = Vector4(1, -1, 0, 0);
		color = Vector4(1, 1, 1, 1);
	};
};

class LightManager : public Singleton<LightManager>
{
	
	ID3D11Buffer*		dirLightBuffer;
public:
	LightManager();
	~LightManager();
	DirLight			dirLight;
	void				Set();
};

