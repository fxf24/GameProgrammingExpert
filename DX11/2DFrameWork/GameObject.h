#pragma once

class GameObject : public Transform
{
	friend class Actor;
	friend class Camera;
	//static
private:
	static ID3D11Buffer*	WBuffer;
	static GameObject*		axis;
public:
	static GameObject* Create(string name = "GameObject");
	static void CreateStaticMember();
	static void DeleteStaticMember();
	//member
public:
	string						name;	//key
	bool						visible;
	class Actor*				root;
	map<string, GameObject*>	children;
	shared_ptr<Shader>			shader;
	shared_ptr<Mesh>			mesh;

	//Method
protected:
	GameObject();
	virtual	~GameObject();
	void			SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void			LoadObject(Xml::XMLElement* This);
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
	void			RenderDetail() override;
};

