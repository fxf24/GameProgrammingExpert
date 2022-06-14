#pragma once

#include <windows.h>
#include <math.h>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

#include "SimpleMath.h"

using namespace DirectX;
using namespace SimpleMath;

#include "GameObject.h"
#include "ObRect.h"

#include "Types.h"
#include "Input.h"
#include "Timer.h"

extern HINSTANCE		g_hInst;
extern HWND				g_hwnd;
extern HDC				g_hdc;
extern HDC				g_MemDC;

#define INPUT Input::GetInstance()
#define TIMER Timer::GetInstance()
#define DELTA Timer::GetInstance()->GetDeltaTime()