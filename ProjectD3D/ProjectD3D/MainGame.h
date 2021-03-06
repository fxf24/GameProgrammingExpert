#pragma once

class MainGame : public Scene
{
private:

	Camera*		Cam;
	Camera*		Cam2;
	vector<Camera*> Cams;

	ObRect		Sun;
	ObRect		SunBone[5];
	ObRect		Planet[5];

public:
	~MainGame();
	void Init() override;
	void Update() override;
	void Render() override;
};

