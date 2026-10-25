#include "stdafx.h"
#include "Coin.h"

extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_Coin = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_Coin = ScreenHeight_Coin / 240; // 缩放倍率

Coin::Coin()
{
    Type = -1;
    loadimage(&OrignImage, "resources/graphics/item_objects.png", 576 * Scale_Coin, 336 * Scale_Coin);
}

void Coin::DrawObject()
{
    if (Type == 1)
    {
        int CropX = SAnimation_Spin.CutXPosition * Scale_Coin;      // 裁剪区域左上角x坐标
        int CropY = 113 * Scale_Coin;      // 裁剪区域左上角y坐标
        int CropWidth = 10 * Scale_Coin; // 裁剪区域宽度
        int CropHeight = 14 * Scale_Coin;// 裁剪区域高度

        DrawImg(CurrentXPosition * Scale_Coin, CurrentYPosition * Scale_Coin, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
    }
}

void Coin::SetType(int InputType)
{
    Type = InputType;
}

void Coin::SetPosition(int InputXPosition, int InputYPosition)
{
    XPosition = InputXPosition;
    YPosition = InputYPosition;
    CurrentXPosition = InputXPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = InputYPosition - G_Camera.GetWorldYPosition();
    SAnimation_Fall.Float_YPosition = YPosition;
    SAnimation_Fall.InitialYPosition = YPosition;
}

void Coin::Animator()
{
    if (Type == 1)
    {
        Animaiton_Fall();
        Animation_Spin();
    }
}

void Coin::Animaiton_Fall()
{
    SAnimation_Fall.InitialYSpeed += SAnimation_Fall.Gravity * (float)G_GameMgr.GetDeltaTime();
    SAnimation_Fall.Float_YPosition += SAnimation_Fall.InitialYSpeed * (float)G_GameMgr.GetDeltaTime();
    YPosition = SAnimation_Fall.Float_YPosition;
    if (SAnimation_Fall.InitialYPosition - YPosition <= 5 && SAnimation_Fall.InitialYSpeed > 0)
    {
        HaveDoneAnimation_Fall();
    }
}

void Coin::Animation_Spin()
{
    if (GetTickCount64() % 300 < 75)
    {
        SAnimation_Spin.CutXPosition = 3;
    }
    else if (GetTickCount64() % 300 < 150)
    {
        SAnimation_Spin.CutXPosition = 19;
    }
    else if (GetTickCount64() % 300 < 225)
    {
        SAnimation_Spin.CutXPosition = 35;
    }
    else if (GetTickCount64() % 300 < 300)
    {
        SAnimation_Spin.CutXPosition = 51;
    }
}

void Coin::HaveDoneAnimation_Fall()
{
    string Text = "200";
    G_GameMgr.AddFloatingText(XPosition, YPosition - 5, Text);
    P_PlayerMario.AddCoinCount(1);
    P_PlayerMario.AddScore(200);

    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecCoins.size(); i++)
    {
        if (this == &G_GameMgr.GameLevelMgr.GameObjectsMgr.vecCoins[i])
        {
            G_GameMgr.GameLevelMgr.GameObjectsMgr.vecCoins.erase(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecCoins.begin() + i);
        }
    }
}

void Coin::Update()
{
    SetCurrentPosition();
    InitCollider();
    Animator();
}