#include "stdafx.h"
#include "Prop.h"

extern Camera G_Camera;
extern GameMgr G_GameMgr;

Prop::Prop()
{
    XPosition = 0;
    YPosition = 0;
    CurrentXPosition = 0;
    CurrentYPosition = 0;
    BoxCollider.ColliderPosition_Left = 0;
    BoxCollider.ColliderPosition_Right = 0;
    BoxCollider.ColliderPosition_Top = 0;
    BoxCollider.ColliderPosition_Button = 0;
    IsEnterColliderWithPlayer = false;
}

void Prop::SetPosition(int InputXPosition, int InputYPosition)
{
    XPosition = InputXPosition;
    YPosition = InputYPosition;
    CurrentXPosition = InputXPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = InputYPosition - G_Camera.GetWorldYPosition();
}

void Prop::SetCurrentPosition()
{
    CurrentXPosition = XPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = YPosition - G_Camera.GetWorldYPosition();
}

void Prop::InitCollider()
{

}

bool Prop::GetIsEnterColliderWithPlayer()
{
    return IsEnterColliderWithPlayer;
}

void Prop::SetIsEnterColliderWithPlayer(bool State)
{
    IsEnterColliderWithPlayer = State;
}

// 判断是否与标签为1的物体重叠的函数

bool Prop::OnEnterColliderLeftWithTag_1() // 判断是否与带有标签1的物体在左侧重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool Prop::OnEnterColliderRightWithTag_1() // 判断是否与带有标签1的物体在右侧重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool Prop::OnEnterColliderTopWithTag_1() // 判断是否与带有标签1的物体在物体的上方重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool Prop::OnEnterColliderButtonWithTag_1() // 判断是否与带有标签1的物体在物体的下方重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}


// 判断是否与方块重叠的函数

bool Prop::OnEnterColliderWithBlock_Left(Block& Block) // 判断是否与砖块在左侧重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Left > BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Right)
        {
            if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool Prop::OnEnterColliderWithBlock_Right(Block& Block) // 判断是否与砖块在右侧重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Left)
        {
            if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * -1 && Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool Prop::OnEnterColliderWithBlock_Top(Block& Block) // 判断是否与砖块在物体的上方重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
        {
            if (Block.BoxCollider.ColliderPosition_Left >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right <= BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool Prop::OnEnterColliderWithBlock_Button(Block& Block) // 判断是否与砖块在物体的下方重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top)
        {
            if (Block.BoxCollider.ColliderPosition_Left >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right <= BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top > Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top > (BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}

// 判断玩家是否贴着标签为1的物体的函数

bool Prop::IsNearLeftWithTag_1() // 判断是否贴着标签为1的物体左侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool Prop::IsNearRightWithTag_1() // 判断是否贴着标签为1的物体右侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool Prop::IsNearTopWithTag_1() // 判断是否贴着标签为1的物体上侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool Prop::IsNearButtonWithTag_1() // 判断是否贴着标签为1的物体下侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}

bool Prop::IsNearBlock_Left(Block& Block) // 判断是否贴着方块左侧的函数
{
    bool IsNear = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right == 1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool Prop::IsNearBlock_Right(Block& Block) // 判断是否贴着方块右侧的函数
{
    bool IsNear = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left == -1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool Prop::IsNearBlock_Top(Block& Block) // 判断是否贴着方块上侧的函数
{
    bool IsNear = false;
    if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Left)
    {
        if (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button == 1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool Prop::IsNearBlock_Button(Block& Block) // 判断是否贴着方块下侧的函数
{
    bool IsNear = false;
    if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Left)
    {
        if (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top == -1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}