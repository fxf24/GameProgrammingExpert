#pragma once

class ObLine :public GameObject
{
	//POINT a;
	Vector2 vertex[2];
	Vector2 endPoint;

public:
	ObLine();
	~ObLine()override;


	void Render() override;
	Vector2 GetEndPoint() { return endPoint; }
};

