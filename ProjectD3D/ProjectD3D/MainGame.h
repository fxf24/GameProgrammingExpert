#pragma once
class MainGame : public Scene
{
private:
	ObRect		rc;

public:
	~MainGame();
	void Init() override;
	void Update() override;
	void Render() override;
};

