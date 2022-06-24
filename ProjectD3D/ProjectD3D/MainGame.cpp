
#include "framework.h"
#include "MainGame.h"



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

    for (int i = 0; i < 4; i++)
    {
        Cams.push_back(new Camera());
    }

    GameObject::cam = Cams[0];

    for (int i = 0; i < 4; i++)
    {
        Cams[i]->position = Vector3(0.0f, 0.0f, -10.0f + 20.0f * (i%2));
    }
    
    Cams[1]->rotation.y = 3.14f;
    Cams[2]->rotation.y = 3.14f;

    vector<pair<int, int>> loc = {
        {0, 0}, {1, 0}, {0,1}, {1, 1}
    };

    for (int i = 0; i < 4; i++)
    {
        Cams[i]->x = 900 * loc[i].first;
        Cams[i]->y = 450 * loc[i].second;

        Cams[i]->w = 900;
        Cams[i]->h = 450;
    }

    Sun.position.x = 0.0f;
    Sun.position.y = 0.0f;

    Sun.scale.x = 1.0f;
    Sun.scale.y = 1.0f;

    for (int i = 0; i < 5; i++)
    {
        Sun.children.push_back(&SunBone[i]);
        SunBone[i].parent = &Sun;

        SunBone[i].children.push_back(&Planet[i]);
        Planet[i].parent = &SunBone[i];

        Planet[i].position.x = 2.0f * (i + 1);
        Planet[i].position.y = 2.0f * (i + 1);

        Planet[i].scale.x = 1.0f;
        Planet[i].scale.y = 1.0f;
    }

}

MainGame::~MainGame()
{
    GameObject::DeleteStaticMember();
}

void MainGame::Update()
{
    if (INPUT->KeyPress('1'))
    {
        Cam->fov += 3.14f * DELTA;
    }
    if (INPUT->KeyPress('2'))
    {
        Cam->fov -= 3.14f * DELTA;
    }


    if (INPUT->KeyPress('A'))
    {
        Cam->position += -Cam->GetRight() * 100.0f * DELTA;
    }
    if (INPUT->KeyPress('D'))
    {
        Cam->position += Cam->GetRight() * 100.0f * DELTA;
    }

    if (INPUT->KeyPress('W'))
    {
        Cam->position += Cam->GetForward() * 100.0f * DELTA;
    }
    if (INPUT->KeyPress('S'))
    {
        Cam->position += -Cam->GetForward() * 100.0f * DELTA;
    }
    Sun.rotation.y += 60.0f * TORADIAN * DELTA;

    for (int i = 0; i < 4; i++)
    {
        Cams[i]->Update();
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

    wstring text = L"FPS:" + to_wstring(TIMER->GetFPS());
    TextOut(g_MemDC, 0, 0, text.c_str(), text.size());

    for (int i = 0; i < 4; i++)
    {
        GameObject::cam = Cams[i];
        Sun.Render();
    }

    //고속 복사 g_MemDC에서 g_hdc로
    BitBlt(g_hdc, 0, 0, 1800, 900,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
