#include "framework.h"

void Rain::CreateStaticMember()
{
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(RAIN_DESC);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &RainBuffer);
		assert(SUCCEEDED(hr));

	}
}

void Rain::DeleteStaticMember()
{
	SafeRelease(RainBuffer);
}

Rain* Rain::Create(string name)
{
	Rain* temp = new Rain();
	temp->name = name;
	//temp->type = ObType::UI;

	temp->mesh = RESOURCE->meshes.Load("7.Billboard.mesh");
	temp->shader = RESOURCE->shaders.Load("7.Rain.hlsl");
	temp->shader->LoadGeometry();


	return temp;
}

void Rain::Render()
{
	desc.time = TIMER->GetWorldTime();

	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(RainBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(RAIN_DESC), &desc, sizeof(RAIN_DESC));
		D3D->GetDC()->Unmap(RainBuffer, 0);
		D3D->GetDC()->VSSetConstantBuffers(10, 1, &RainBuffer);
	}

	Actor::Render();
}
