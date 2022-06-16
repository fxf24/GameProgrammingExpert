#pragma once
class MainGame : public Scene
{
private:
	ObRect	rc;
	ObRect	rc2;
	ObRect	rc3;

	ObRect	rc4;
	ObRect	rc5;

	ObRect	rc6;
	ObRect	rc7;

	ObRect	rc8;
	ObRect	rc9;


public:
	~MainGame();
	void Init() override;
	void Update() override;
	void Render() override;
};

