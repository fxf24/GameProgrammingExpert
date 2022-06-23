#pragma once
class Camera : public GameObject
{
public:
	Matrix view,proj,viewport;
	float fov;
	float x, y, w, h;
	Camera();
	~Camera();
	void Update() override;

	static Matrix CreateViewport(float x, float y, float w, float h, float minz, float maxz);
};

