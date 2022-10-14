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
<<<<<<< HEAD

    Cam2 = Camera::Create();
    Cam2->LoadFile("Cam.xml");

    LoadingCount++;

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
    LoadingCount++;

    Camera::main = Cam;

=======
    Camera::main = Cam;

    Cam2 = Camera::Create();
    Cam2->LoadFile("Cam.xml");

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int j = 0; j < ARRAY_SIZE; j++)
        {
            for (int k = 0; k < ARRAY_SIZE; k++)
            {
                Sphere[i][j][k] = Actor::Create();
                Sphere[i][j][k]->LoadFile("Sphere.xml");
<<<<<<< HEAD

=======
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
                Sphere[i][j][k]->SetWorldPosX(i * 4.0f);
                Sphere[i][j][k]->SetWorldPosY(j * 4.0f);
                Sphere[i][j][k]->SetWorldPosZ(k * 4.0f);
            }
        }
    }
<<<<<<< HEAD
  



=======
    ResizeScreen();
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
}

void Scene2::Release()
{
    RESOURCE->ReleaseAll();
<<<<<<< HEAD
=======

    Grid->Release();

>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
}


void Scene2::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
<<<<<<< HEAD
   
    Grid->RenderHierarchy();
    Cam2->RenderHierarchy();
=======
    Grid->RenderHierarchy();
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
    Cam->RenderHierarchy();
    Cam2->RenderHierarchy();
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
<<<<<<< HEAD
                {
                    RenderList.push_back(Sphere[i][j][k]);
                }
               
=======
                RenderList.push_back(Sphere[i][j][k]);
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
            }
        }
    }
   
}

void Scene2::Render()
{

<<<<<<< HEAD


=======
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
    Cam->Set();
    Cam2->Set();
    Grid->Render();
<<<<<<< HEAD

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
=======
    
    for (int i = 0; i<RenderList.size(); i++)
    {
        RenderList[i]->Update();
    }
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
}

void Scene2::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}