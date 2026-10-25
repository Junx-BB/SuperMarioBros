#include "stdafx.h"
#include "Brick.h"

extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;
extern MusicMgr G_MusicMgr;

Brick::Brick()
{
    Tag = 1;
    Type = 0;
    IsEnterColliderWithPlayer_Top = false;
    SAnimation_Floating.IsFloating = false;
    SAnimation_Floating.CurrentSpeed = SAnimation_Floating.InitialSpeed;
    loadimage(&OrignImage, "resources/graphics/tile_set.png");
}

void Brick::DrawObject()
{
    int CropX = 16;     // 裁剪区域左上角x坐标
    int CropY = 0;      // 裁剪区域左上角y坐标
    int CropWidth = 16; // 裁剪区域宽度
    int CropHeight = 16;// 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void Brick::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 15;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}

void Brick::SetType(int InputType)
{
    Type = InputType;
}

int Brick::GetTag()
{
    return Tag;
}

bool Brick::GetIsEnterColliderWithPlayer_Top()
{
    return IsEnterColliderWithPlayer_Top;
}

void Brick::SetIsEnterColliderWithPlayer_Top(bool State)
{
    IsEnterColliderWithPlayer_Top = State;
}

// 当物体碰撞箱子与其它物体碰撞箱重叠时触发的函数
void Brick::OnCollitionEnter() 
{
    if (IsEnterColliderWithPlayer_Top == true)
    {
        if (P_PlayerMario.GetIsBig() == false)
        {
            InitAnimation_Floating();
            G_MusicMgr.Play_Bump();
        }
        if (P_PlayerMario.GetIsBig() == true)
        {
            G_MusicMgr.Play_BrickSmash();
        }
        OnCollitionEnterWithPlayer_Top();
        IsEnterColliderWithPlayer_Top = false;
    }
}

// 与玩家在其上方重叠时调用的函数
void Brick::OnCollitionEnterWithPlayer_Top()
{
    if (P_PlayerMario.GetIsBig() == false)
    {
        SAnimation_Floating.IsFloating = true;
    }
    if (P_PlayerMario.GetIsBig() == true)
    {
        Animation_Disappear();
    }
}

void Brick::InitAnimation_Floating()
{
    SAnimation_Floating.InitialYPosition = YPosition;
    SAnimation_Floating.Float_YPosition = YPosition;
}

void Brick::Animator()
{
    if (SAnimation_Floating.IsFloating == true)
    {
        Animation_Floating();
    }
}

void Brick::Animation_Floating()
{
    SAnimation_Floating.CurrentSpeed += 1 * 1;
    SAnimation_Floating.Float_YPosition += SAnimation_Floating.CurrentSpeed * 1;
    YPosition = SAnimation_Floating.Float_YPosition;
    if (SAnimation_Floating.Float_YPosition >= SAnimation_Floating.InitialYPosition)
    {
        SAnimation_Floating.IsFloating = false;
        SAnimation_Floating.Float_YPosition = SAnimation_Floating.InitialYPosition;
        YPosition = SAnimation_Floating.InitialYPosition;
        SAnimation_Floating.CurrentSpeed = SAnimation_Floating.InitialSpeed;
    }
}

void Brick::Animation_Disappear()
{
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (this == &G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i])
        {
            G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.erase(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.begin() + i);
        }
    }
}


void Brick::Update()
{
    SetCurrentPosition();
    InitCollider();
    OnCollitionEnter();
    Animator();
}