
#include "framework.h"
#include "MainGame.h"


void MainGame::Init()
{
    //MemDc 메모리상의 dc를 하나더 추가
    HBITMAP	 m_hOldBitmap, m_hBitmap;
    HDC	hdc = GetDC(g_hwnd); //기존핸들
    g_MemDC = CreateCompatibleDC(hdc);	//
    m_hBitmap = CreateCompatibleBitmap(hdc, 1800, 900);//만들크기
    m_hOldBitmap = (HBITMAP)SelectObject(g_MemDC, m_hBitmap);
    ReleaseDC(g_hwnd, hdc);
    
    Sun.position.x = 900.0f;
    Sun.position.y = 400.0f;

    Sun.scale.x = 100.0f;
    Sun.scale.y = 100.0f;

    power = 0;
    rotate = false;
    for (int i = 0; i < 5; i++)
    {
        Sun.children.push_back(&SunBone[i]);
        SunBone[i].parent = &Sun;

        SunBone[i].children.push_back(&Planet[i]);
        Planet[i].parent = &SunBone[i];

        Planet[i].position.x = 80.0f * (i + 1);
        Planet[i].position.y = 80.0f * (i + 1);

        Planet[i].scale.x = 50.0f;
        Planet[i].scale.y = 50.0f;
    }

}
MainGame::~MainGame()
{
}

void MainGame::Update()
{
    if (INPUT->KeyDown(VK_SPACE))
    {
        rotate = true;
        power += 720.0f;
    }

    if (INPUT->KeyPress(VK_UP) )
    {
        // 초당 100 변화량
        Sun.position.y -= DELTA * 100;
    }
    if (INPUT->KeyPress(VK_DOWN) )
    {
        Sun.position.y += DELTA * 100;
    }
    if (INPUT->KeyPress(VK_LEFT) )
    {
        Sun.position.x -= DELTA * 100;
    }
    if (INPUT->KeyPress(VK_RIGHT) )
    {
        Sun.position.x += DELTA * 100;
    }
    if (INPUT->KeyPress('1'))
    {
        Sun.rotation += DELTA * TORADIAN * 360.0f;
    }
    if (INPUT->KeyPress('2'))
    {
        Sun.rotation -= 0.02f;
    }
    if (INPUT->KeyPress('3'))
    {
        Sun.scale.x += 0.1f;
    }
    if (INPUT->KeyPress('4'))
    {
        Sun.scale.x -= 0.1f;
    }
    if (INPUT->KeyPress('5'))
    {
        Sun.scale.y += 0.1f;
    }
    if (INPUT->KeyPress('6'))
    {
        Sun.scale.y -= 0.1f;
    }
    //Sun.rotation += DELTA * TORADIAN * 10.0f;

    if (rotate)
    {
        Sun.rotation += DELTA * TORADIAN * power;

        power -= 2.0f;
        if (power <= 0.0f)
        {
            rotate = not rotate;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        //SunBone[i].rotation += DELTA * TORADIAN * 30.0f * (i + 1);
    }

    Sun.Update();

    InvalidateRect(g_hwnd, NULL, false);
}

void MainGame::Render()
{
    PAINTSTRUCT ps;
    g_hdc = BeginPaint(g_hwnd, &ps);

    //바탕색 깔기
    PatBlt(g_MemDC, 0, 0, 1800, 900,WHITENESS);

    wstring text = L"FPS: " + to_wstring(TIMER->GetFPS());
    TextOut(g_MemDC, 0, 0, text.c_str(), text.size());
    wstring text2 = L"Click Space to Spin";
    TextOut(g_MemDC, 0, 20, text2.c_str(), text2.size());

    Sun.Render();
    /*MoveToEx(g_MemDC,100,100,nullptr);
    LineTo(g_MemDC, 200, 100);
    LineTo(g_MemDC, 200, 200);

    MoveToEx(g_MemDC, 100+300, 100, nullptr);
    LineTo(g_MemDC, 200 + 300, 100);
    LineTo(g_MemDC, 200 + 300, 200);*/


    //고속 복사 g_MemDC에서 g_hdc로
    BitBlt(g_hdc, 0, 0, 1800, 900,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
