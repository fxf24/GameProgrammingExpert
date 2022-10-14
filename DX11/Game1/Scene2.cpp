#include "stdafx.h"

Scene2::Scene2()
{
   
}

Scene2::~Scene2()
{
 
}

void Scene2::Init()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");

    Cam2 = Camera::Create();
    Cam2->LoadFile("Cam.xml");

    LoadingCount++;

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
    LoadingCount++;

    Camera::main = Cam;


    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ARRAY_SIZE; j++)
        {
            for (int k = 0; k < ARRAY_SIZE; k++)
            {
                Sphere[i][j][k] = Actor::Create();
                Sphere[i][j][k]->LoadFile("Sphere.xml");

                Sphere[i][j][k]->SetWorldPosX(i * 4.0f);
                Sphere[i][j][k]->SetWorldPosY(j * 4.0f);
                Sphere[i][j][k]->SetWorldPosZ(k * 4.0f);
            }
        }
    }
  



}

void Scene2::Release()
{
    RESOURCE->ReleaseAll();
}


void Scene2::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
   
    Grid->RenderHierarchy();
    Cam2->RenderHierarchy();
    Cam->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Cam2->Update();
    Grid->Update();
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ARRAY_SIZE; j++)
        {
            for (int k = 0; k < ARRAY_SIZE; k++)
            {
                Sphere[i][j][k]->Update();
            }
        }
    }
}

void Scene2::LateUpdate()
{
    Plane A;
    BoundingFrustum B;
    RenderList.clear();

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ARRAY_SIZE; j++)
        {
            for (int k = 0; k < ARRAY_SIZE; k++)
            {
                if (Cam2->Intersect(Sphere[i][j][k]->GetWorldPos()))
                {
                    RenderList.push_back(Sphere[i][j][k]);
                }
               
            }
        }
    }
   
}

void Scene2::Render()
{



    Cam->Set();
    Grid->Render();

    for (int i = 0; i < RenderList.size(); i++)
    {
        RenderList[i]->Render();
    }

    /*for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ARRAY_SIZE; j++)
        {
            for (int k = 0; k < ARRAY_SIZE; k++)
            {
                Sphere[i][j][k]->Render();
            }
        }
    }*/
}

void Scene2::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}