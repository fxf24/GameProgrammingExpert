#pragma once
class MainGame : public Scene
{
private:
	ObRect		rc;
	ObRect		rc2;
	ObRect		rc3;

public:
	~MainGame();
	void Init() override;
	void Update() override;
	void Render() override;
};

