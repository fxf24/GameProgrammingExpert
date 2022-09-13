#pragma once
class UI : public Actor
{
public:
	static UI* Create(string name = "UI");
	bool			Press = false;
	virtual void	Update() override;
	function<void()> mouseOver = nullptr; // ���콺�� ���� �����Ҷ�
	function<void()> mouseDown = nullptr; // ������ �������� �ѹ�
	function<void()> mousePress = nullptr; // ������ ������
	function<void()> mouseUp = nullptr; // ������ ��������
};

