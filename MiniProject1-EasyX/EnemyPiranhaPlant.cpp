#include "stdafx.h"
#include "EnemyPiranhaPlant.h"


extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_PiranhaPlant = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_PiranhaPlant = ScreenHeight_PiranhaPlant / 240;// 缩放倍率

EnemyPiranhaPlant::EnemyPiranhaPlant(int XPosition, int YPosition, int XSpeed, int YSpeed, int direction, int Tag, int step_num, int T_Wait, int frames, int f_speed, int index) :
    EnemyBase(XPosition, YPosition, XSpeed, YSpeed, direction, Tag, step_num, frames, f_speed, index), T_Wait(T_Wait) {
}

void EnemyPiranhaPlant::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 17;
    BoxCollider.ColliderPosition_Top = YPosition + 8;
    BoxCollider.ColliderPosition_Button = YPosition + 24;
}

//移动
void EnemyPiranhaPlant::Move()
{
    if (direction == 0)
    {
        YPosition -= YSpeed;
    }
    else
    {
        YPosition += YSpeed;
    }
}

//改变方向
void EnemyPiranhaPlant::ChangeDirection()
{
    auto& PipeTops = G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops;
    for (int i = 0; i < PipeTops.size(); i++)
    {
        if (BoxCollider.ColliderPosition_Left > PipeTops[i].BoxCollider.ColliderPosition_Left && BoxCollider.ColliderPosition_Right < PipeTops[i].BoxCollider.ColliderPosition_Right)
        {
            if (BoxCollider.ColliderPosition_Button == PipeTops[i].BoxCollider.ColliderPosition_Top || BoxCollider.ColliderPosition_Top == PipeTops[i].BoxCollider.ColliderPosition_Button)
            {
                direction = (direction + 1) % 2;
                YSpeed = 0;
                T_Wait++;
                if (T_Wait == 41)
                {
                    YSpeed = 1;
                    T_Wait = 0;
                }
            }
        }
    }
}

//死亡
void EnemyPiranhaPlant::Die()
{
    YPosition = 350;
}

void EnemyPiranhaPlant::Update()
{
    //更新实际位置
    SetCurrentPosition();

    //更新碰撞箱
    InitCollider();

    //在一定范围来回移动
    ChangeDirection();

    //上下移动
    Move();

    if (step_num == 3)
    {
        //死亡
        Die();
    }
}

void EnemyPiranhaPlant::Render()
{
    auto& PipeTops = G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (BoxCollider.ColliderPosition_Left >= PipeTops[i].BoxCollider.ColliderPosition_Left && BoxCollider.ColliderPosition_Right <= PipeTops[i].BoxCollider.ColliderPosition_Right)
        {
            DrawImg(CurrentXPosition * Scale_PiranhaPlant, CurrentYPosition * Scale_PiranhaPlant, 17 * Scale_PiranhaPlant, (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i].BoxCollider.ColliderPosition_Top - YPosition) * Scale_PiranhaPlant, &img_Enemy, (356 + index * 18) * Scale_PiranhaPlant, 0 * Scale_PiranhaPlant);
        }
    }
    index = (GetTickCount64() / f_speed % frames);
    frameTime = GetTickCount64() - frameStart;
}