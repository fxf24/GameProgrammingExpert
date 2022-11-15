#include "stdafx.h"

BlurManager::BlurManager()
{
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(Blur);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &blurBuffer);
       
        assert(SUCCEEDED(hr));
    }
}

BlurManager::~BlurManager()
{
    SafeRelease(blurBuffer);
}

void BlurManager::Update()
{
    ImGui::SliderInt("_Filter", &blur._Filter, 0, 5);
    ImGui::SliderInt("_Select", &blur._Select, 0, 7);
    ImGui::SliderInt("_Count", &blur._Count, 1, 1000);
    ImGui::DragFloat("_Width", &blur._Width, 0.05f);
    ImGui::DragFloat("_Height", &blur._Height, 0.05f);
    ImGui::ColorEdit3("_Color", (float*)&blur._Color, ImGuiColorEditFlags_PickerHueWheel);
    ImGui::DragFloat("_Radius", &blur._Radius, 0.05f);
    ImGui::DragFloat2("_Screen", (float*)&blur._Screen, 0.05f);
}

void BlurManager::Set()
{
   D3D11_MAPPED_SUBRESOURCE mappedResource;
   D3D->GetDC()->Map(blurBuffer, 0, D3D11_MAP_WRITE_DISCARD,0,&mappedResource);
   memcpy_s(mappedResource.pData, sizeof(Blur), &blur, sizeof(Blur));
   D3D->GetDC()->Unmap(blurBuffer, 0);
   D3D->GetDC()->PSSetConstantBuffers(10, 1, &blurBuffer);
}
