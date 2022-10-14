#pragma once
class Camera : public Actor
{
private:
	static ID3D11Buffer* VPBuffer;
	static ID3D11Buffer* viewPosBuffer;
	static ID3D11Buffer* viewUpBuffer;
	static ID3D11Buffer* viewForwardBuffer;
public:
	static Camera* main;
public:
	static void CreateStaticMember();
	static void DeleteStaticMember();
	static void ControlMainCam(float scalar = 10.0f);
	static Camera* Create(string name = "Camera");
private:
	
public:
	Matrix		view, proj;
	bool		ortho;
	Viewport	viewport;
	float		fov,nearZ,farZ, width, height;
protected:
	Camera();
	~Camera();
public:
	void	Update() override;
	void	Set();
	void	RenderDetail();
	bool    Intersect(Vector3 coord);
};

