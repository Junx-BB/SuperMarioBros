#include "stdafx.h"
#include "GrowMushroom.h"

extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;
extern MusicMgr G_MusicMgr;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_GrowMushroom = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_GrowMushroom = ScreenHeight_GrowMushroom / 240; // 缩放倍率

GrowMushroom::GrowMushroom()
{
    loadimage(&OrignImage, "resources/graphics/item_objects.png",576 * Scale_GrowMushroom,336 * Scale_GrowMushroom);
}

void GrowMushroom::DrawObject()
{
    int CropX = 0 * Scale_GrowMushroom;      // 裁剪区域左上角x坐标
    int CropY = 0 * Scale_GrowMushroom;      // 裁剪区域左上角y坐标
    int CropWidth = 16 * Scale_GrowMushroom; // 裁剪区域宽度
    int CropHeight = (16 - SAnimation_Emerge.CutOffset_Y) * Scale_GrowMushroom;// 裁剪区域高度

    DrawImg(CurrentXPosition * Scale_GrowMushroom, (CurrentYPosition + SAnimation_Emerge.CutOffset_Y) * Scale_GrowMushroom, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void GrowMushroom::SetPosition(int InputXPosition, int InputYPosition)
{
    XPosition = InputXPosition;
    YPosition = InputYPosition;
    CurrentXPosition = InputXPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = InputYPosition - G_Camera.GetWorldYPosition();
    SAnimation_Move.InitialXPosition = XPosition;
}

void GrowMushroom::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 15;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}

// 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
void GrowMushroom::OnCollitionEnter()
{
    OnCollitionEnterWithPlayer();
    OnCollitionEnterWithTag_1();
}

// 与玩家重叠时调用的函数
void GrowMushroom::OnCollitionEnterWithPlayer()
{
    if (IsEnterColliderWithPlayer == true)
    {
        if (P_PlayerMario.GetIsBig() == false)
        {
            P_PlayerMario.SetIsTransformingBig(true);
            G_MusicMgr.Play_PowerUp();
        }
        if (P_PlayerMario.GetIsBig() == true)
        {

        }

        string Text = "1000";
        G_GameMgr.AddFloatingText(XPosition, YPosition - 5, Text);
        P_PlayerMario.AddScore(1000);

        for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGrowMushrooms.size(); i++)
        {
            if (this == &G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGrowMushrooms[i])
            {
                G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGrowMushrooms.erase(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGrowMushrooms.begin() + i);
            }
        }
    }
}
    
    

void GrowMushroom::OnCollitionEnterWithTag_1()
{
    while (OnEnterColliderLeftWithTag_1() == true)
    {
        XPosition--;
        SAnimation_Move.Ditection = -1;
        InitCollider();
    }
    while (OnEnterColliderRightWithTag_1() == true)
    {
        XPosition++;
        SAnimation_Move.Ditection = 1;
        InitCollider();
    }
    while (OnEnterColliderTopWithTag_1() == true)
    {
        YPosition--;
        InitCollider();
    }
    while (OnEnterColliderButtonWithTag_1() == true)
    {
        YPosition++;
        InitCollider();
    }
}

void GrowMushroom::Animator()
{
    Animation_Move();
    Animaiton_Fall();
    Animation_Emerge();
}

void GrowMushroom::Animation_Move()
{
    if (SAnimation_Emerge.IsEmerging == false)
    {
        SAnimation_Move.AccumulativeXPosition += SAnimation_Move.Ditection * SAnimation_Move.XSpeed;
        XPosition = SAnimation_Move.InitialXPosition + SAnimation_Move.AccumulativeXPosition;
    }
}

void GrowMushroom::Animation_Emerge()
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

void GrowMushroom::Animaiton_Fall()
{
    if (SAnimation_Emerge.IsEmerging == false)
    {
        if (IsNearTopWithTag_1() == true)
        {
            SAnimation_Fall.OnGround = true;
            SAnimation_Fall.CurrentYSpeed = 0;
        }
        else if (IsNearTopWithTag_1() == false)
        {
            SAnimation_Fall.OnGround = false;
        }

        if (SAnimation_Fall.OnGround == false)
        {
            SAnimation_Fall.CurrentYSpeed += SAnimation_Fall.Gravity * 0.25;
            YPosition += SAnimation_Fall.CurrentYSpeed * 0.25;
        }
    }
}

void GrowMushroom::Update()
{
    SetCurrentPosition();
    InitCollider();
    OnCollitionEnter();
    Animator();
}