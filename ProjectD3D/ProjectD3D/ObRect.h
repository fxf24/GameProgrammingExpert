#pragma once
class ObRect :public GameObject
{
	//POINT a;
	Vector3 vertex[4];
public:
	ObRect();
	~ObRect()override;
	

	void Render() override;
};

