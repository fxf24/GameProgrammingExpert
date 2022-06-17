#pragma once
#include "Bullet.h"

class MainGame : public Scene
{
private:
	ObRect		Sun;
	Bullet		bullet[20];

public:
	~MainGame();
	void Init() override;
	void Update() override;
	void Render() override;
};

