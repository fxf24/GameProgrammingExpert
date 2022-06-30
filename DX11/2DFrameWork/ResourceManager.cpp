#include "framework.h"

const shared_ptr<Mesh>& ResourceManager::LoadMesh(string file)
{
	auto it = meshes.find(file);

	// 찾았다.
	if (it != meshes.end())
	{
		return it->second;
	}

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->LoadFile(file);
	meshes[file] = mesh;

	return meshes[file];
}

const shared_ptr<Shader>& ResourceManager::LoadShader(string file)
{
	auto it = shaders.find(file);

	// 찾았다.
	if (it != shaders.end())
	{
		return it->second;
	}
	shared_ptr<Shader> shader = make_shared<Shader>();
	int vertype = file[0] - 48;

	shader->LoadFile(file, (VertexType)vertype);
	shaders[file] = shader;

	return shaders[file];
}

void ResourceManager::ReleaseAll()
{
	for (auto it = meshes.begin(); it != meshes.end(); it++)
	{
		SafeReset(it->second);
	}
	meshes.clear();

	for (auto it = shaders.begin(); it != shaders.end(); it++)
	{
		SafeReset(it->second);
	}
	shaders.clear();
}