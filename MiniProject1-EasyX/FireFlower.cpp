#include "stdafx.h"
#include "FireFlower.h"

extern MusicMgr G_MusicMgr;

extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_FireFlower = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_FireFlower = ScreenHeight_FireFlower / 240; // 缩放倍率

FireFlower::FireFlower()
{
    loadimage(&OrignImage, "resources/graphics/item_objects.png", 576 * Scale_FireFlower, 336 * Scale_FireFlower);
}

void FireFlower::DrawObject()
{
    int CropX = (0 + SAnimation_Blink.CutOffset_X) * Scale_FireFlower; ;    // 裁剪区域左上角x坐标
    int CropY = 32 * Scale_FireFlower;      // 裁剪区域左上角y坐标
    int CropWidth = 16 * Scale_FireFlower; // 裁剪区域宽度
    int CropHeight = (16 - SAnimation_Emerge.CutOffset_Y) * Scale_FireFlower;// 裁剪区域高度

    DrawImg(CurrentXPosition * Scale_FireFlower, (CurrentYPosition + SAnimation_Emerge.CutOffset_Y) * Scale_FireFlower, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void FireFlower::SetPosition(int InputXPosition, int InputYPosition)
{
    XPosition = InputXPosition;
    YPosition = InputYPosition;
    CurrentXPosition = InputXPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = InputYPosition - G_Camera.GetWorldYPosition();
}

void FireFlower::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 15;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}

// 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
void FireFlower::OnCollitionEnter()
{
    OnCollitionEnterWithPlayer();
}

// 与玩家重叠时调用的函数
void FireFlower::OnCollitionEnterWithPlayer()
{
      
}

void FireFlower::Animator()
{
    Animation_Emerge();
    Animation_Blink();
}

void FireFlower::Animation_Emerge()
{
    if (SAnimation_Emerge.IsEmerging == true)
    {
        SAnimation_Emerge.Timer += (float)G_GameMgr.GetDeltaTime();
        if (SAnimation_Emerge.Timer >= 0.5)
        {
            if (SAnimation_Emerge.CutOffset_Y == 16)
            {
                G_MusicMgr.Play_PowerUpAppear();
            }
            SAnimation_Emerge.CutOffset_Y--;
            if (SAnimation_Emerge.CutOffset_Y <= 0)
            {
                SAnimation_Emerge.IsEmerging = false;
                SAnimation_Emerge.CutOffset_Y = 0;
            }
        }
    }
}

void FireFlower::Animation_Blink()
{
    if (GetTickCount64() % 200 < 50)
    {
        SAnimation_Blink.CutOffset_X = 0;
    }
    else if (GetTickCount64() % 200 < 100)
    {
        SAnimation_Blink.CutOffset_X = 16;
    }
    else if (GetTickCount64() % 200 < 150)
    {
        SAnimation_Blink.CutOffset_X = 32;
    }
    else if (GetTickCount64() % 200 < 200)
    {
        SAnimation_Blink.CutOffset_X = 48;
    }
}

void FireFlower::Update()
{
    SetCurrentPosition();
    InitCollider();
    OnCollitionEnter();
    Animator();
}