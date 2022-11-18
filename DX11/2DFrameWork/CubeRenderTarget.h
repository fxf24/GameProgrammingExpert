#pragma once
class CubeRenderTarget
{
protected:
    int width, height;

    ID3D11RenderTargetView* rtv;
    ID3D11DepthStencilView* dsv;


    //���̴��ڿ����� ���� �������̽�
    ID3D11ShaderResourceView* rtvSrv;

    //�ڿ�
    ID3D11Texture2D* rtvTexture;
    ID3D11Texture2D* dsvTexture;
    //â������ ����
    void CreateBackBuffer(float width, float height);
    void DeleteBackBuffer();
public:

    CubeRenderTarget(int width = 256, int height = 256);
    ~CubeRenderTarget();

    void Set(Color clear = Color(0, 0, 0, 1));

    ID3D11ShaderResourceView* GetSRV() { return rtvSrv; }

    //â������ ����
    virtual void ResizeScreen(float width, float height);
};

