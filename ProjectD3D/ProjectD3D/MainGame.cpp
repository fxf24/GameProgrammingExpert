
#include "framework.h"
#include "MainGame.h"



void MainGame::Init()
{
    GameObject::CreateStaticMember();


    //MemDc �޸𸮻��� dc�� �ϳ��� �߰�
    HBITMAP	 m_hOldBitmap, m_hBitmap;
    HDC	hdc = GetDC(g_hwnd); //�����ڵ�
    g_MemDC = CreateCompatibleDC(hdc);	//
    m_hBitmap = CreateCompatibleBitmap(hdc, 1800, 900);//����ũ��
    m_hOldBitmap = (HBITMAP)SelectObject(g_MemDC, m_hBitmap);
    ReleaseDC(g_hwnd, hdc);

    Cam = new Camera();
    Cam2 = new Camera();
    GameObject::cam = Cam;

    Cam->position = Vector3(0.0f, 0.0f, -10.0f);
    Cam2->position = Vector3(0.0f, 0.0f, 10.0f);
    Cam2->rotation.y = 3.14f;

    Cam->x = 900.0f;
    Cam->w = 900.0f;
    Cam2->w = 900.0f;

    //
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

    Cam->Update();
    Cam2->Update();
    Sun.Update();

    InvalidateRect(g_hwnd, NULL, false);
}

void MainGame::Render()
{
    PAINTSTRUCT ps;
    g_hdc = BeginPaint(g_hwnd, &ps);

    //������ ���
    PatBlt(g_MemDC, 0, 0, 1800, 900,WHITENESS);

    wstring text = L"FPS:" + to_wstring(TIMER->GetFPS());
    TextOut(g_MemDC, 0, 0, text.c_str(), text.size());

    GameObject::cam = Cam;
    Sun.Render();
    GameObject::cam = Cam2;
    Sun.Render();

    //��� ���� g_MemDC���� g_hdc��
    BitBlt(g_hdc, 0, 0, 1800, 900,
        g_MemDC, 0, 0, SRCCOPY);

    EndPaint(g_hwnd, &ps);
}
