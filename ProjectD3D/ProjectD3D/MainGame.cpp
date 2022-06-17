
#include "framework.h"
#include "MainGame.h"
#include "Bullet.h"

void MainGame::Init()
{
    GameObject::CreateStaticMember();

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

}

MainGame::~MainGame()
{
    GameObject::DeleteStaticMember();
}

void MainGame::Update()
{
    Vector2 Dir = g_Mouse - Sun.position;
    Dir.Normalize();

    Sun.rotation = atan2f(Dir.y, Dir.x);

    if (INPUT->KeyPress('W'))
    {
        Sun.position += Vector2(0, -1) * DELTA * 100;
    }
    if (INPUT->KeyPress('S'))
    {
        Sun.position += Vector2(0, 1) * DELTA * 100;
    }
    if (INPUT->KeyPress('A'))
    {
        Sun.position += Vector2(-1, 0) * DELTA * 100;
    }
    if (INPUT->KeyPress('D'))
    {
        Sun.position += Vector2(1, 0) * DELTA * 100;
    }

    if (INPUT->KeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < 20; i++)
        {
            if (not bullet[i].visible)
            {
                bullet[i].Shoot(Sun.position, Sun.GetRight(), 1800.0f);
                break;
            }
        }
    }

    Sun.Update();
    for (int i = 0; i < 20; i++)
    {
        bullet[i].Update();
    }
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
    wstring text2 = L"Click Space to Shoot";
    TextOut(g_MemDC, 0, 20, text2.c_str(), text2.size());
    wstring text3 = L"Press WASD to Move";
    TextOut(g_MemDC, 0, 40, text3.c_str(), text3.size());
    /*wstring text4 = L"Ammo : " + to_wstring(10 - (int)bullet_count);
    TextOut(g_MemDC, 0, 60, text4.c_str(), text4.size());*/

    Sun.Render();

    for (int i = 0; i < 20; i++)
    {
        bullet[i].Render();
    }

    //고속 복사 g_MemDC에서 g_hdc로
    BitBlt(g_hdc, 0, 0, 1800, 900,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
