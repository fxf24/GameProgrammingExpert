#include "framework.h"

GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	parent = nullptr;
	visible = true;

	shader = nullptr;
	shader = new Shader();
	shader->LoadFile("1.Cube.hlsl", VertexType::PC);
	mesh = new Mesh();
	//cout << "in" << endl;
	mesh->LoadFile("1.Sphere.mesh");
}

void GameObject::Update()
{
	//if (not active)return;



	S = Matrix::CreateScale(scale.x, scale.y, scale.z);
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	T = Matrix::CreateTranslation(position.x, position.y, position.z);
	RT = R * T;
	W = S * RT;
	if (parent)
	{
		W *= parent->RT;
		RT *= parent->RT;
	}
	//재귀호출
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Update();
	}

}

void GameObject::Render()
{
	Matrix TW = W.Transpose();
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D->GetDC()->Map(WBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy_s(mappedResource.pData, sizeof(Matrix), &TW, sizeof(Matrix));
	D3D->GetDC()->Unmap(WBuffer, 0);
	
	if (visible)
	{
		//GameObject::Render();
		shader->Set();
		if (mesh)
		{
			mesh->Set();
			D3D->GetDC()->DrawIndexed(mesh->indexCount, 0,0);
		}
	}


	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Render();
	}
}

ID3D11Buffer* GameObject::WBuffer = nullptr;

void GameObject::CreateStaticMember()
{
	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = sizeof(Matrix);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &WBuffer);
	assert(SUCCEEDED(hr));

	D3D->GetDC()->VSSetConstantBuffers(0, 1, &WBuffer);
}

void GameObject::DeleteStaticMember()
{
	SafeRelease(WBuffer);
}
