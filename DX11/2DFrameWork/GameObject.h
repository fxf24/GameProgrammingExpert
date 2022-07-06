#pragma once

class GameObject : public Transform
{
	friend class Actor;
	//static
private:
	static ID3D11Buffer* WBuffer;
public:
	static GameObject* Create(string name = "GameObject");
	static void CreateStaticMember();
	static void DeleteStaticMember();
	//member
public:
	string						name;	//key
	class Actor*				root;
	GameObject*					parent;
	map<string, GameObject*>	children;
	shared_ptr<Shader>			shader;
	shared_ptr<Mesh>			mesh;

	//Method
protected:
	GameObject();
	virtual ~GameObject();
	void  SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void  LoadObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
public:
	void Release();
	virtual void Update();
	virtual void Render();
	void AddChild(GameObject* child);
	bool RenderHierarchy();
	virtual void RenderDetail();

	//Getter Setter
};
class Actor : public GameObject
{
	friend GameObject;
private:
	unordered_map<string, GameObject*> obList;
public:
	string			file;
private:
	Actor();
public:
	void			Release();
	void			ReleaseMember();
	static Actor*	Create(string name = "Actor");
	GameObject*		Find(string name);
	bool            DeleteObject(string Name);
	void			Save(string file);
	void			Load(string file);
	void			RenderDetail();
};

