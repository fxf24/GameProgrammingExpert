#pragma once
class ObRect :public GameObject
{
	//POINT a;
	VertexP			vertex[4];
	ID3D11Buffer*	vertexBuffer;
public:
	ObRect();
	~ObRect()override;
	

	void Render() override;
};

