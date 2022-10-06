#include "framework.h"

LightManager::LightManager()
{
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(DirLight);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &dirLightBuffer);
        assert(SUCCEEDED(hr));
        D3D->GetDC()->PSSetConstantBuffers(2, 1, &dirLightBuffer);
    }
}

LightManager::~LightManager()
{
    SafeRelease(dirLightBuffer);
}

void LightManager::Set()
{
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        D3D->GetDC()->Map(dirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        memcpy_s(mappedResource.pData, sizeof(DirLight), &dirLight, sizeof(DirLight));
        D3D->GetDC()->Unmap(dirLightBuffer, 0);
    }
}
