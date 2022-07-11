#include "framework.h"

Camera::Camera()
{
    fov = 60.0f * TORADIAN;
    x = y = 0.0f;
    w = App.GetWidth();
    h = App.GetHeight();
	position.z = -10.0f;
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

    
	view = RT.Invert();
    
}
void Camera::Set()
{
	proj = Matrix::CreatePerspectiveFieldOfView(
		fov, w / h, 0.001f, 1000.0f);

    Matrix TVP = view * proj;
    TVP = TVP.Transpose();
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    D3D->GetDC()->Map(VPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy_s(mappedResource.pData, sizeof(Matrix), &TVP, sizeof(Matrix));
    D3D->GetDC()->Unmap(VPBuffer, 0);

    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}


ID3D11Buffer* Camera::VPBuffer = nullptr;
Camera* Camera::main = nullptr;
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

void Camera::ControlMainCam(float scalar)
{
    if (not main) return;

	if (INPUT->KeyPress('W'))
	{
		//                                  초당100움직임 xyz/s
		main->position += main->GetForward() * DELTA * scalar;
	}
	if (INPUT->KeyPress('S'))
	{
		main->position -= main->GetForward() * DELTA * scalar;
	}
	if (INPUT->KeyPress('A'))
	{
		main->position -= main->GetRight() * DELTA * scalar;
	}
	if (INPUT->KeyPress('D'))
	{
		main->position += main->GetRight() * DELTA * scalar;
	}
	if (INPUT->KeyPress('Q'))
	{
		main->position += main->GetUp() * DELTA * scalar;
	}
	if (INPUT->KeyPress('E'))
	{
		main->position -= main->GetUp() * DELTA * scalar;
	}

	//마우스 우클릭시
	if (INPUT->KeyPress(VK_RBUTTON))
	{
		Vector3 Rot;
		Rot.x = INPUT->movePosition.y * 0.001f;
		Rot.y = INPUT->movePosition.x * 0.001f;
		main->rotation += Rot;
	}
	//휠키로 카메라 앞뒤조절
	main->position+= main->GetForward() * INPUT->wheelMoveValue.z * DELTA * scalar;
}
