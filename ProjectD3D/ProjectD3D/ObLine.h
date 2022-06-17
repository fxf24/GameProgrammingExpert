#pragma once

class ObLine :public GameObject
{
	//POINT a;
	Vector2 vertex[2];
public:
	ObLine();
	~ObLine()override;


	void Render() override;
};

