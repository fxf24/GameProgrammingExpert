#include "framework.h"

Camera::Camera()
{
	fov = 60.0f * TORADIAN;
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	width= App.GetWidth();
	height = App.GetHeight();
	viewport.width = App.GetWidth();
	viewport.height = App.GetHeight();
	nearZ = 0.001f;
	farZ = 1000.0f;
	type = ObType::Camera;
	ortho = false;
}
Camera::~Camera()
{
}

Camera* Camera::Create(string name)
{
	Camera* temp = new Camera();
	temp->name = name;
	return temp;
}

void Camera::Update()
{
    GameObject::Update();
}
void Camera::Set()
{
	{
		view = RT.Invert();
		if (ortho)
			proj = Matrix::CreateOrthographic(width, height, nearZ, farZ);
		else
			proj = Matrix::CreatePerspectiveFieldOfView(fov, width / height, nearZ, farZ);
		Matrix TVP = view * proj;
		TVP = TVP.Transpose();
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(VPBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Matrix), &TVP, sizeof(Matrix));
		D3D->GetDC()->Unmap(VPBuffer, 0);

		D3D->GetDC()->VSSetConstantBuffers(1, 1, &VPBuffer);
		D3D->GetDC()->GSSetConstantBuffers(0, 1, &VPBuffer);
	}
	{
		Vector4 viewPos = Vector4(GetWorldPos().x, GetWorldPos().y, GetWorldPos().z,1.0f);
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(viewPosBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Vector4), &viewPos, sizeof(Vector4));
		D3D->GetDC()->Unmap(viewPosBuffer, 0);
		D3D->GetDC()->PSSetConstantBuffers(0, 1, &viewPosBuffer);
		D3D->GetDC()->GSSetConstantBuffers(1, 1, &viewPosBuffer);
	}
	{
		Vector3 viewUp = GetUp();
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(viewUpBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Vector4), &viewUp, sizeof(Vector4));
		D3D->GetDC()->Unmap(viewUpBuffer, 0);
		D3D->GetDC()->GSSetConstantBuffers(2, 1, &viewUpBuffer);
	}
	{
		Vector3 viewForward = GetForward();
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(viewForwardBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(Vector4), &viewForward, sizeof(Vector4));
		D3D->GetDC()->Unmap(viewForwardBuffer, 0);
		D3D->GetDC()->GSSetConstantBuffers(3, 1, &viewForwardBuffer);
	}
    D3D->GetDC()->RSSetViewports(1, viewport.Get11());
}

ID3D11Buffer* Camera::VPBuffer = nullptr;
ID3D11Buffer* Camera::viewPosBuffer = nullptr;
ID3D11Buffer* Camera::viewUpBuffer = nullptr;
ID3D11Buffer* Camera::viewForwardBuffer = nullptr;
Camera* Camera::main = nullptr;
void Camera::CreateStaticMember()
{
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
		
	}
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(Vector4);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &viewPosBuffer);
		assert(SUCCEEDED(hr));
		
	}
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(Vector4);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &viewUpBuffer);
		assert(SUCCEEDED(hr));

	}
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(Vector4);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &viewForwardBuffer);
		assert(SUCCEEDED(hr));

	}
    
}

void Camera::DeleteStaticMember()
{
    SafeRelease(VPBuffer);
    SafeRelease(viewPosBuffer);
    SafeRelease(viewUpBuffer);
    SafeRelease(viewForwardBuffer);
}

void Camera::ControlMainCam(float scalar)
{
    if (not main) return;

	if (INPUT->KeyPress('W'))
	{
		//                                  초당100움직임 xyz/s
		main->MoveWorldPos(main->GetForward() * DELTA * scalar);
	}
	if (INPUT->KeyPress('S'))
	{
		main->MoveWorldPos(-main->GetForward() * DELTA * scalar);
	}
	if (INPUT->KeyPress('A'))
	{
		main->MoveWorldPos(-main->GetRight() * DELTA * scalar);
	}
	if (INPUT->KeyPress('D'))
	{
		main->MoveWorldPos(main->GetRight() * DELTA * scalar);
	}
	if (INPUT->KeyPress('Q'))
	{
		main->MoveWorldPos(-main->GetUp() * DELTA * scalar);
	}
	if (INPUT->KeyPress('E'))
	{
		main->MoveWorldPos(main->GetUp() * DELTA * scalar);
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
	main->MoveWorldPos(main->GetForward() * INPUT->wheelMoveValue.z * DELTA);
}

bool Camera::Intersect(Vector3 coord)
{
	BoundingFrustum Frustum;

	Frustum.Origin = GetWorldPos();
	Frustum.Orientation = Quaternion::CreateFromRotationMatrix(R);
	Frustum.RightSlope = tanf(fov);
	Frustum.LeftSlope = -Frustum.RightSlope;
	Frustum.TopSlope = Frustum.RightSlope * App.GetHeight() / App.GetWidth();
	Frustum.BottomSlope = -Frustum.TopSlope;
	Frustum.Near = nearZ;
	Frustum.Far = farZ;

	if (Frustum.Contains(coord) != DISJOINT)
	{
		return true;
	}

	return false;
}