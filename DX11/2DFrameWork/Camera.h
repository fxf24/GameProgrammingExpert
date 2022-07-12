#pragma once
class Camera : public Actor
{
private:
	static ID3D11Buffer* VPBuffer;
public:
	static Camera* main;
public:
	static void CreateStaticMember();
	static void DeleteStaticMember();
	static void ControlMainCam(float scalar = 10.0f);
private:
	Viewport	viewport;
	Matrix		view,proj;
public:
	float fov,nearZ,farZ;
	float x, y, w, h;
	Camera();
	~Camera();
	void Update() override;
	void Set();
	//상수버퍼
	
	void SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void LoadObject(Xml::XMLElement* This);
};

