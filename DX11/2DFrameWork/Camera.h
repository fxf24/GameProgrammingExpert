#pragma once
class Camera : public GameObject
{
	Viewport	viewport;
	Matrix		view,proj;
public:

	

	float fov;
	float x, y, w, h;
	Camera();
	~Camera();
	void Update() override;
	void Set();
	//상수버퍼
	static ID3D11Buffer* VPBuffer;
	static Camera* main;

	static void CreateStaticMember();
	static void DeleteStaticMember();
	static void ControlMainCam(float scalar = 100.0f);
};

