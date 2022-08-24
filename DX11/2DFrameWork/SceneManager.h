#pragma once
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, Scene*> scenes;
	Scene* currentScene = nullptr;
	Scene* nextScene = nullptr;
	bool isChanging = false;
	float changingTime = 0.0f;
public :
	~SceneManager();

	bool AddScene(string key, Scene* value);
	bool DeleteScene(string key);
	Scene* ChangeScene(string key, float changingTime = 0.0f);
	Scene* GetScene(string key);
	Scene* GetCurrentScene();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	void ResizeScreen();
};

