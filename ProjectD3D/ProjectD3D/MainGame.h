#pragma once
class MainGame : public Scene
{
private:
	ObRect		Sun;
	ObRect		SunBone[5];
	
	ObRect		Planet[5];

	vector<ObRect*> bullet;
	vector<Vector2> bullet_dir;

	float		power;
	float		bullet_count = 0;

public:
	~MainGame();
	void Init() override;
	void Update() override;
	void Render() override;
};

