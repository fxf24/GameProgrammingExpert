#pragma once
class GameObject
{
protected:
	GameObject();

public:
	bool				visible;
	Vector3				position;
	Vector3				scale;
	Vector3				rotation;

	string				name;  //key
	class Actor*		root;
	GameObject*			parent;
	vector<GameObject*> children;
	shared_ptr<Shader>	shader;
	shared_ptr<Mesh>	mesh;

	Matrix		S, R, T, RT, W;


	//상수버퍼
	static ID3D11Buffer* WBuffer;

	virtual ~GameObject();

	//생성함수
	static GameObject* Create(string name = "GameObject");

	virtual void Update();
	virtual void Render();

	void AddChild(GameObject* child);

	static void CreateStaticMember();
	static void DeleteStaticMember();

	bool RenderImGui();

	Vector3 GetRight() { return Vector3(RT._11, RT._12,RT._13); }
	Vector3 GetUp() { return Vector3(RT._21, RT._22, RT._23); }
	Vector3 GetForward() { return Vector3(RT._31, RT._32, RT._33); }
};

class Actor : public GameObject
{
	friend GameObject;
private:
	Actor();
	unordered_map<string, GameObject*> obList;
public:
	GameObject* Find(string name);
	static Actor* Create(string name = "Actor");
};