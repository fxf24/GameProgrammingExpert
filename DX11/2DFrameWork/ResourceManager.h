#pragma once
class ResourceManager : public Singleton<ResourceManager>
{
private:
	unordered_map<string, shared_ptr<Mesh>> meshes;
	unordered_map<string, shared_ptr<Shader>> shaders;
public:
	const shared_ptr<Mesh>& LoadMesh(string file);
	const shared_ptr<Shader>& LoadShader(string file);

	void ReleaseAll();
};

