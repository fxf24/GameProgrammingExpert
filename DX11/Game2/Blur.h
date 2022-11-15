#pragma once
struct Blur
{
	int     _Filter = 0;
	Vector3  _Color = Vector3(0.5, 0.5, 0.5);
	Vector2  _Screen = Vector2(App.GetHalfWidth(), App.GetHalfHeight());
	float   _Radius = 2000.0f;
	int		_Count = 1;
	int		_Select = 0;
	float	_Width = App.GetWidth();
	float	_Height = App.GetHeight();
	float   _Padding;
};

class BlurManager :public Singleton< BlurManager>
{
	ID3D11Buffer* blurBuffer;
public:
	BlurManager();
	~BlurManager();
	Blur	blur;
	void Update();
	void Set();
};

