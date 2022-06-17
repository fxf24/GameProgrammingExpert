#include "framework.h"

ObLine::ObLine()
{
	vertex[0] = Vector2(0.0f, 0.0f);
	vertex[1] = Vector2(1.0f, 0.0f);
}

ObLine::~ObLine()
{
}

void ObLine::Render()
{
    if (visible)
    {
        Vector2 TransfomVertex[2];

        for (int i = 0; i < 2; i++)
        {
            TransfomVertex[i] = Vector2::Transform(vertex[i], W);
        }
        //0->1->2->3->0

        MoveToEx(g_MemDC, TransfomVertex[0].x, TransfomVertex[0].y, NULL);
        LineTo(g_MemDC, TransfomVertex[1].x, TransfomVertex[1].y);
    }

    // ¿Á±Õ »£√‚
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->Render();
    }
}
