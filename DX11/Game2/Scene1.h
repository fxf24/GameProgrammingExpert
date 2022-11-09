#pragma once
class Scene1 : public Scene
{
private:
	Camera* Cam;

	Sky* sky;
	CubeMan* player;
	Ray		cubeManTopRay;

	Actor* Point;
	Actor* Arrow;
	Light* Point2;
	Terrain* Map;

	Int2   Pos;


	//ù���� ����Ÿ��
	CubeMap* cubeMap = nullptr;
	Shader* cubeMappingShader;
	Shader* cubeMappingShader2;
	Shader* cubeMappingShader3;
	Actor*	sphere;

	//�ι�° ���� Ÿ��
	RenderTarget* RT = nullptr;
	UI* PostEffect;
	float refractionIdx = 1.0f;

	Rain* rain;
	Rain* skill;
	float skill_time = 1.0f;

	Vector3			from, to;
	float			lerpValue;

	float			Rfrom, Rto;
	float			RlerpValue;

	bool findPath = false;
	int route = -1;
	vector<Vector3> path;
public:
	Scene1();
	~Scene1();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

