#pragma once
class CubeMap
{
private:
    static ID3D11Buffer* camBuffer;

    UINT width, height;

    ID3D11RenderTargetView* rtv;
    ID3D11DepthStencilView* dsv;


    //���̴��ڿ����� ���� �������̽�
    ID3D11ShaderResourceView* rtvSrv;
    //ID3D11ShaderResourceView* dsvSrv;

    //�ڿ�
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

    void Set(Vector3  position, float zNear = 0.1f, float zFar = 500.0f, Color clear = Color(0, 0, 0, 1));

    ID3D11ShaderResourceView* GetRTVSRV() { return rtvSrv; }
    //ID3D11ShaderResourceView* GetDSVSRV() { return dsvSrv; }
    ID3D11RenderTargetView* GetRTV() { return rtv; }
    ID3D11DepthStencilView* GetDSV() { return dsv; }

    //â������ ����
    //void ResizeScreen(float width, float height);

    ////â������ ����
    //void CreateBackBuffer(float width, float height);
    //void DeleteBackBuffer();
};

