#pragma once
class RenderTarget
{
protected:
    int width, height;

    //���� ����Ÿ������ ���� �ʿ��� �������̽�
    ID3D11RenderTargetView* rtv;
    ID3D11DepthStencilView* dsv;


    //���̴��ڿ����� ���� �������̽�
    ID3D11ShaderResourceView* rtvSrv;
    ID3D11ShaderResourceView* dsvSrv;

    //�ڿ�
    ID3D11Texture2D* rtvTexture;
    ID3D11Texture2D* dsvTexture;

    //â������ ����
    void CreateBackBuffer(float width, float height);
    void DeleteBackBuffer();

public:
    RenderTarget(UINT width = App.GetWidth() ,
        UINT height = App.GetHeight());
    ~RenderTarget();

    void Set(Color clear = Color(0, 0, 0, 1));

    ID3D11ShaderResourceView* GetSRV() { return rtvSrv; }

    //â������ ����
    void ResizeScreen(float width, float height);
};

