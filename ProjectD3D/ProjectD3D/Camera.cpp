#include "framework.h"

Camera::Camera()
{
   
    x = 0.0f;
    y = 0.0f;
    w = 1800.0f;
    h = 900.0f;
    fov = 60.0f * TORADIAN;
}

Camera::~Camera()
{
}

void Camera::Update()
{
    GameObject::Update();
    
    viewport = CreateViewport(x, y, w, h, 0.0f, 1.0f);
    proj = Matrix::CreatePerspectiveFieldOfView(
        fov, 1800.0f / 900.0f, 0.001f, 1000.0f);

    view = RT.Invert(); // ¿ªÇà·Ä

}

Matrix Camera::CreateViewport(float x, float y, float w, float h, float minz, float maxz)
{
    Matrix viewport;
    viewport._11 = w / 2.0f;
    viewport._22 = -h / 2.0f;
    viewport._33 = maxz - minz;
    viewport._41 = x + w / 2.0f;
    viewport._42 = y + h / 2.0f;
    viewport._43 = minz;
    return viewport;
}
