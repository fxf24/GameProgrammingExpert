#include "framework.h"

Camera::Camera()
{
    fov = 60.0f * TORADIAN;
    x = y = 0.0f;
    w = 1800.0f;
    h = 900.0f;
}

Camera::~Camera()
{
}

void Camera::Update()
{
    GameObject::Update();

    viewport.x = x;
    viewport.y = y;
    viewport.width = w;
    viewport.height = h;

    proj = Matrix::CreatePerspectiveFieldOfView(
        fov, 1800.0f / 900.0f, 0.001f, 1000.0f);

    view = RT.Invert();
    
}
void Camera::Set()
{
    Matrix TVP = view * proj;
    TVP = TVP.Transpose();
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    D3D->GetDC()->Map(VPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy_s(mappedResource.pData, sizeof(Matrix), &TVP, sizeof(Matrix));
    D3D->GetDC()->Unmap(VPBuffer, 0);

    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}


ID3D11Buffer* Camera::VPBuffer = nullptr;
void Camera::CreateStaticMember()
{
    D3D11_BUFFER_DESC desc = { 0 };
    desc.ByteWidth = sizeof(Matrix);
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;
    HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &VPBuffer);
    assert(SUCCEEDED(hr));
    D3D->GetDC()->VSSetConstantBuffers(1, 1, &VPBuffer);
}

void Camera::DeleteStaticMember()
{
    SafeRelease(VPBuffer);
}