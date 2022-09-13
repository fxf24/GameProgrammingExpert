#pragma once
class UI : public Actor
{
public:
	static UI* Create(string name = "UI");
	bool			Press = false;
	virtual void	Update() override;
	function<void()> mouseOver = nullptr; // 마우스가 위에 존재할때
	function<void()> mouseDown = nullptr; // 위에서 눌렀을때 한번
	function<void()> mousePress = nullptr; // 누르고 있을때
	function<void()> mouseUp = nullptr; // 눌렀다 떼었을때
};

