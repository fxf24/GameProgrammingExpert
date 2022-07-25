#pragma once

enum class ObType
{
	GameObject,
	Actor,
	Camera
};

class GameObject : public Transform
{
	friend class Actor;
	//static
private:
	static GameObject*		axis;
	static Material*		defalutMaterial;
public:
	static GameObject* Create(string name = "GameObject");
	static void CreateStaticMember();
	static void DeleteStaticMember();
	//member
protected:
	ObType						type;
public:
	string						name;	//key
	bool						visible;
	class Actor*				root;
	map<string, GameObject*>	children;
	shared_ptr<Shader>			shader;
	shared_ptr<Mesh>			mesh;
	shared_ptr<Material>		material;
	Collider*					collider;
	//Method
protected:
	GameObject();
	virtual	~GameObject();
	void	SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void	LoadObject(Xml::XMLElement* This);
public:
	void			Release();
	virtual void	Update();
	virtual void	Render();
	void			AddChild(GameObject* child);
	bool			RenderHierarchy();
	virtual void	RenderDetail();

	//Getter Setter
};


class Actor : public GameObject
{
	friend GameObject;
private:
	unordered_map<string, GameObject*> obList;
public:
	string			file;
protected:
	Actor();
public:
	void			Release();
	void			ReleaseMember();
	static Actor*	Create(string name = "Actor");
	GameObject*		Find(string name);
	bool            DeleteObject(string Name);
	void			SaveFile(string file);
	void			LoadFile(string file);
	virtual void	RenderDetail();
};

