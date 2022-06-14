
#include "framework.h"
#include "MainGame.h"


void MainGame::Init()
{
    //MemDc 메모리상의 dc를 하나더 추가
    HBITMAP	 m_hOldBitmap, m_hBitmap;
    HDC	hdc = GetDC(g_hwnd); //기존핸들
    g_MemDC = CreateCompatibleDC(hdc);	//
    m_hBitmap = CreateCompatibleBitmap(hdc, 800, 600);//만들크기
    m_hOldBitmap = (HBITMAP)SelectObject(g_MemDC, m_hBitmap);
    ReleaseDC(g_hwnd, hdc);
    //
    rc.position.x = 400.0f;
    rc.position.y = 300.0f;

    rc.scale.x = 100.0f;
    rc.scale.y = 100.0f;

    rc.rotation = 0.0f;

}
MainGame::~MainGame()
{
}

void MainGame::Update()
{
    if (INPUT->KeyPress(VK_UP) )
    {
        rc.position.y += 0.5f;
    }
    if (INPUT->KeyPress(VK_DOWN) )
    {
        rc.position.y -= 0.5f;
    }
    if (INPUT->KeyPress(VK_LEFT) )
    {
        rc.position.x -= 0.5f;
    }
    if (INPUT->KeyPress(VK_RIGHT) )
    {
        rc.position.x += 0.5f;
    }
    if (INPUT->KeyPress('1'))
    {
        rc.rotation += 0.1f;
    }
    if (INPUT->KeyPress('2'))
    {
        rc.rotation -= 0.1f;
    }
    if (INPUT->KeyPress('3'))
    {
        rc.scale.x += 0.1f;
    }
    if (INPUT->KeyPress('4'))
    {
        rc.scale.x -= 0.1f;
    }
    if (INPUT->KeyPress('5'))
    {
        rc.scale.y += 0.1f;
    }
    if (INPUT->KeyPress('6'))
    {
        rc.scale.y -= 0.1f;
    }
    rc.Update();

    InvalidateRect(g_hwnd, NULL, false);
}

void MainGame::Render()
{
    PAINTSTRUCT ps;
    g_hdc = BeginPaint(g_hwnd, &ps);

    //바탕색 깔기
    PatBlt(g_MemDC, 0, 0, 800, 600,WHITENESS);

    
    rc.Render();


    /*MoveToEx(g_MemDC,100,100,nullptr);
    LineTo(g_MemDC, 200, 100);
    LineTo(g_MemDC, 200, 200);

    MoveToEx(g_MemDC, 100+300, 100, nullptr);
    LineTo(g_MemDC, 200 + 300, 100);
    LineTo(g_MemDC, 200 + 300, 200);*/


    //고속 복사 g_MemDC에서 g_hdc로
    BitBlt(g_hdc, 0, 0, 800, 600,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
