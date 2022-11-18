#pragma once
class Environment : public CubeRenderTarget
{
private:
    static ID3D11Buffer* camBuffer;
    static ID3D11Buffer* PSBuffer;

    struct GSCamBuffer
    {
        Matrix Views[6];
        Matrix Projection;
    } desc;
    struct PSCubeMap
    {
        int CubeMapType = 0;
        float RefractIndex = 1.0f;
        float WaterIndex = 0.01f;
        float CubeMapPadding;
        Matrix Rotation;
    };
    Viewport    viewport;
    Vector3     position;

public:
    Environment(UINT width = 256, UINT height = 256);
    ~Environment();
    shared_ptr<Texture> water;
    shared_ptr<Texture> environment;
    PSCubeMap desc2;
    Vector3   rot;

    static void CreateStaticMember();
    static void DeleteStaticMember();


    virtual void ResizeScreen(float width, float height);

    void RenderDetail();

    void SetCapture(Vector3 position, float fov = PI_DIV2, float zNear = 0.1f, float zFar = 1000.0f, Color clear = Color(0, 0, 0, 1));

    void SetTexture();
};

