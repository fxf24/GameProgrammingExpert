
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

    rc.scale.x = 50.0f;
    rc.scale.y = 50.0f;

    rc.rotation = 0.0f;

    rc.children.push_back(&rc2);
    rc2.parent = &rc;

    rc2.position.x = 80.0f;
    rc2.position.y = 80.0f;
      
    rc2.scale.x = 25.0f;
    rc2.scale.y = 25.0f;
      
    rc2.rotation = 0.0f;

    rc2.children.push_back(&rc3);
    rc3.parent = &rc2;
      
    rc3.position.x = 20.0f;
    rc3.position.y = 20.0f;
      
    rc3.scale.x = 5.0f;
    rc3.scale.y = 5.0f;
      
    rc3.rotation = 0.0f;


    rc.children.push_back(&rc4);
    rc4.parent = &rc;
      
    rc4.position.x = 140.0f;
    rc4.position.y = -140.0f;
      
    rc4.scale.x = 25.0f;
    rc4.scale.y = 25.0f;
      
    rc4.rotation = 0.0f;

    rc4.children.push_back(&rc5);
    rc5.parent = &rc4;

    rc5.position.x = 20.0f;
    rc5.position.y = 20.0f;

    rc5.scale.x = 5.0f;
    rc5.scale.y = 5.0f;

    rc5.rotation = 0.0f;


    rc.children.push_back(&rc6);
    rc6.parent = &rc;

    rc6.position.x = -180.0f;
    rc6.position.y = -180.0f;

    rc6.scale.x = 25.0f;
    rc6.scale.y = 25.0f;

    rc6.rotation = 0.0f;

    rc6.children.push_back(&rc7);
    rc7.parent = &rc6;

    rc7.position.x = 20.0f;
    rc7.position.y = 20.0f;

    rc7.scale.x = 5.0f;
    rc7.scale.y = 5.0f;

    rc7.rotation = 0.0f;

    rc.children.push_back(&rc8);
    rc8.parent = &rc;

    rc8.position.x = -220.0f;
    rc8.position.y = 220.0f;

    rc8.scale.x = 25.0f;
    rc8.scale.y = 25.0f;

    rc8.rotation = 0.0f;

    rc8.children.push_back(&rc9);
    rc9.parent = &rc8;

    rc9.position.x = 20.0f;
    rc9.position.y = 20.0f;

    rc9.scale.x = 5.0f;
    rc9.scale.y = 5.0f;

    rc9.rotation = 0.0f;

}
MainGame::~MainGame()
{
}

void MainGame::Update()
{
   /* if (INPUT->KeyPress(VK_UP) )
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
        rc.rotation += 0.02f;
    }
    if (INPUT->KeyPress('2'))
    {
        rc.rotation -= 0.02f;
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
    }*/
    rc.rotation += 0.01f;
    rc2.rotation += 0.02f;
    rc3.rotation += 0.03f;

    rc4.rotation += 0.03f;
    rc5.rotation += 0.04f;
    
    rc6.rotation += 0.04f;
    rc7.rotation += 0.05f;

    rc8.rotation += 0.05f;
    rc9.rotation += 0.06f;

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
