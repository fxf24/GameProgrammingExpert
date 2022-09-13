#include "framework.h"

UI* UI::Create(string name)
{
	UI* temp = new UI();
	temp->name = name;
	return temp;
}

void UI::Update()
{
	Actor::Update();

	float left, right, top, bottom;

	left = GetWorldPos().x - S._11 * 0.5;
	right = GetWorldPos().x + S._11 * 0.5;
	top = GetWorldPos().y + S._22 * 0.5;
	bottom = GetWorldPos().y - S._22 * 0.5;

	if (left <= INPUT->NDCPosition.x and right >= INPUT->NDCPosition.x and bottom <= INPUT->NDCPosition.y and top >= INPUT->NDCPosition.y)
	{
		//함수포인터가 할당 되었다면 실행
		if (mouseOver) mouseOver();

		if (INPUT->KeyDown(VK_LBUTTON))
		{
			if (mouseDown) mouseDown();
		}

		if (INPUT->KeyPress(VK_LBUTTON))
		{
			Press = true;
			if (mousePress) mousePress();
		}

		
	}

	if (Press)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (mousePress) mousePress();
		}

		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Press = false;
			if (mouseUp) mouseUp();
		}
	}
	
}
