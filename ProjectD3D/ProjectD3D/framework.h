#pragma once
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

#include <windows.h>
#include <math.h>
#include <string>
#include <chrono>
#include <vector>
#include <iostream>

using namespace std;

#include "SimpleMath.h"

using namespace DirectX;
using namespace SimpleMath;

#include "GameObject.h"
#include "ObRect.h"
#include "Camera.h"

#include "Types.h"
#include "Input.h"
#include "Timer.h"

extern HINSTANCE           g_hInst;
extern HWND                g_hwnd;
extern HDC                 g_hdc;
extern HDC                 g_MemDC;
extern Vector2             g_Mouse;

#define INPUT Input::GetInstance()
#define TIMER Timer::GetInstance()
#define DELTA Timer::GetInstance()->GetDeltaTime()

#define TORADIAN 0.01745329f

