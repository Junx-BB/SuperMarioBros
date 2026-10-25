#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <string.h>
#include <mmsystem.h>
#include<stdio.h>
#include "GameMgr.h"
#include "Camera.h"
#include "MusicMgr.h"

#pragma comment(lib, "winmm.lib")

#define KEY_DOWN(vk_code)(GetAsyncKeyState(vk_code)&0x8000?1:0)

using namespace std;