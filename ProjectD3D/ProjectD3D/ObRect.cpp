#include "framework.h"

ObRect::ObRect()
{
    vertex[0] = Vector2(-0.5f, -0.5f);
    vertex[1] = Vector2(-0.5f, 0.5f);
    vertex[2] = Vector2(0.5f, 0.5f);
    vertex[3] = Vector2(0.5f, -0.5f);
}

ObRect::~ObRect()
{
}

void ObRect::Render()
{
    //������ ù��ġ�� ����

    //������ �̵�����ġ�� �޾��� ��������
    Vector2 TransfomVertex[4];

    for (int i = 0; i < 4; i++)
    {
        // �̵�����ǥ  = ���ؽ� * W;
        // �̵�����ǥ  = ���ؽ� * S*R*T;
        TransfomVertex[i] = Vector2::Transform(vertex[i], W);
    }
    //0->1->2->3->0

    MoveToEx(g_MemDC, TransfomVertex[0].x, TransfomVertex[0].y, NULL);
    LineTo(g_MemDC, TransfomVertex[1].x, TransfomVertex[1].y);
    LineTo(g_MemDC, TransfomVertex[2].x, TransfomVertex[2].y);
    LineTo(g_MemDC, TransfomVertex[3].x, TransfomVertex[3].y);
    LineTo(g_MemDC, TransfomVertex[0].x, TransfomVertex[0].y);

    // ��� ȣ��
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->Render();
    }
}
