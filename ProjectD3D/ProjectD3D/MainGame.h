#pragma once
class MainGame : public Scene
{
private:
	ObRect		Sun;
	ObRect		SunBone[5];
	
	ObRect		Planet[5];

	bool		rotate;
	float		power;


public:
	~MainGame();
	void Init() override;
	void Update() override;
	void Render() override;
};

