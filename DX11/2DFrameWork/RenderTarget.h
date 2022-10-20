#pragma once
class RenderTarget
{
private:
	UINT width, height;

	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;

	ID3D11ShaderResourceView* rtvSrv;
	ID3D11ShaderResourceView* dsvSrv;

	ID3D11Texture2D* rtvTexture;
	ID3D11Texture2D* dsvTexture;

public:
	RenderTarget(UINT width = App.GetWidth(), UINT height = App.GetHeight());
	~RenderTarget();


};

