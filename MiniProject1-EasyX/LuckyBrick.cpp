#include "stdafx.h"
#include "LuckyBrick.h"

extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;
extern MusicMgr G_MusicMgr;

LuckyBrick::LuckyBrick()
{
    Tag = 1;
    Type = 0;
    IsEmpty = false;
    IsEnterColliderWithPlayer_Top = false;
    SAnimation_Floating.CurrentSpeed = SAnimation_Floating.InitialSpeed;
    loadimage(&OrignImage, "resources/graphics/tile_set.png");
}

void LuckyBrick::DrawObject()
{
    int CropX = 384;     // 裁剪区域左上角x坐标
    int CropY = 0;      // 裁剪区域左上角y坐标
    int CropWidth = 16; // 裁剪区域宽度
    int CropHeight = 16;// 裁剪区域高度

    if (IsEmpty == false)
    {
        if (GetTickCount64() % 750 < 350)
        {
            putimage(CurrentXPosition, CurrentYPosition + SAnimation_Floating.DrawOffset_Y, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
        }
        else if (GetTickCount64() % 750 < 550)
        {
            putimage(CurrentXPosition, CurrentYPosition + SAnimation_Floating.DrawOffset_Y, CropWidth, CropHeight, &OrignImage, CropX += 16, CropY);// 绘制图像
        }
        else if (GetTickCount64() % 750 < 750)
        {
            putimage(CurrentXPosition, CurrentYPosition + SAnimation_Floating.DrawOffset_Y, CropWidth, CropHeight, &OrignImage, CropX += 32, CropY); // 绘制图像
        }
    }
    else if (IsEmpty == true)
    {
        putimage(CurrentXPosition, CurrentYPosition + SAnimation_Floating.DrawOffset_Y, CropWidth, CropHeight, &OrignImage, CropX -= 336, CropY); // 绘制图像
    }
}

void LuckyBrick::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 15;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}

void LuckyBrick::SetType(int InputType)
{
    Type = InputType;
}

int LuckyBrick::GetTag()
{
    return Tag;
}

bool LuckyBrick::GetIsEnterColliderWithPlayer_Top()
{
    return IsEnterColliderWithPlayer_Top;
}

void LuckyBrick::SetIsEnterColliderWithPlayer_Top(bool State)
{
    IsEnterColliderWithPlayer_Top = State;
}

// 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
void LuckyBrick::OnCollitionEnter()
{
    if (IsEmpty == false)
    {
        if (IsEnterColliderWithPlayer_Top == true)
        {
        
                IsEnterColliderWithPlayer_Top = false;
                IsEmpty = true;
                G_MusicMgr.Play_Bump();
                InitAnimation_Floating();
                OnCollitionEnterWithPlayer_Top();
        }
    }
}

// 与玩家在其上方重叠时调用的函数
void LuckyBrick::OnCollitionEnterWithPlayer_Top()
{
    SAnimation_Floating.IsFloating = true;
    if (Type == 0)
    {
        G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCoin(XPosition + 3, YPosition - 14, 1);
        G_MusicMgr.Play_Coin();
    }
    else if (Type == 1)
    {
        if (P_PlayerMario.GetIsBig() == false)
        {
            G_GameMgr.GameLevelMgr.GameObjectsMgr.AddGrowMushroom(XPosition, YPosition - 16);
        }
        if (P_PlayerMario.GetIsBig() == true)
        {
            G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFireFlower(XPosition, YPosition - 16);
        }
    }
    else if (Type == 2)
    {

    }
}

void LuckyBrick::InitAnimation_Floating()
{
    SAnimation_Floating.Float_YPosition = YPosition;
}

void LuckyBrick::Animator()
{
    if (SAnimation_Floating.IsFloating == true)
    {
        Animation_Floating();
    }
}

void LuckyBrick::Animation_Floating()
{
    SAnimation_Floating.CurrentSpeed += 1 * 1;
    SAnimation_Floating.Float_YPosition += SAnimation_Floating.CurrentSpeed * 1;
    SAnimation_Floating.DrawOffset_Y = SAnimation_Floating.Float_YPosition- YPosition;
    if (SAnimation_Floating.Float_YPosition >= YPosition)
    {
        SAnimation_Floating.IsFloating = false;
        SAnimation_Floating.Float_YPosition = YPosition;
        SAnimation_Floating.DrawOffset_Y = 0;
        SAnimation_Floating.CurrentSpeed = SAnimation_Floating.InitialSpeed;
    }
}


void LuckyBrick::Update()
{
    SetCurrentPosition();
    InitCollider();
    OnCollitionEnter();
    Animator();
}