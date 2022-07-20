#include "framework.h"

void ResourceManager::ReleaseAll()
{
	meshes.ReleaseList();
	shaders.ReleaseList();
	textures.ReleaseList(); 
	materials.ReleaseList();
}
//template<typename T>
// const shared_ptr<T>& Resource<T>::Load(string file)
