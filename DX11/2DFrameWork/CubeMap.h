#pragma once
class CubeMap
{
private:
    static ID3D11Buffer* camBuffer;

    UINT width, height;

    ID3D11RenderTargetView* rtv;
    ID3D11DepthStencilView* dsv;


    //쉐이더자원으로 쓸때 인터페이스
    ID3D11ShaderResourceView* rtvSrv;
    //ID3D11ShaderResourceView* dsvSrv;

    //자원
    ID3D11Texture2D* rtvTexture;
    ID3D11Texture2D* dsvTexture;

    struct GSCamBuffer
    {
        Matrix Views[6];
        Matrix Projection;
    } desc;
    Viewport    viewport;
    Vector3     position;

  
public:
  
    static void CreateStaticMember();
    static void DeleteStaticMember();


    CubeMap(UINT width = 256, UINT height = 256);
    ~CubeMap();

    void Set(Vector3  position, float fov = PI_DIV2,float zNear = 0.1f, float zFar = 500.0f, Color clear = Color(0, 0, 0, 1));

    ID3D11ShaderResourceView* GetRTVSRV() { return rtvSrv; }
    //ID3D11ShaderResourceView* GetDSVSRV() { return dsvSrv; }
    ID3D11RenderTargetView* GetRTV() { return rtv; }
    ID3D11DepthStencilView* GetDSV() { return dsv; }

    //창사이즈 조절
    void ResizeScreen(float width, float height);

    //창사이즈 조절
    void CreateBackBuffer(float width, float height);
    void DeleteBackBuffer();
};

