#include "framework.h"

Billboard* Billboard::Create(string name)
{
	Billboard* temp = new Billboard();
	temp->name = name;
	temp->type = ObType::Billboard;
	temp->mesh = RESOURCE->meshes.Load("7.Billboard.mesh");
	temp->shader = RESOURCE->shaders.Load("7.Cube.hlsl");
	return temp;
}

void Billboard::Update()
{
	Actor::Update();
}

void Billboard::Render()
{
	VertexPS* vertex = (VertexPS*)mesh->vertices;
	vertex[0].size = Vector2(S._11, S._22);
	mesh->UpdateMesh();
	Actor::Render();
}
