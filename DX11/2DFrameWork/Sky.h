#pragma once
class Sky : public Actor
{
public:
	shared_ptr<Texture> texCube;
	static Sky* Create(string name = "Sky");
	virtual void	Update() override;
	virtual void	Render() override;
};

