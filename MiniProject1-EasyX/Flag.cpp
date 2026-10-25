#include "stdafx.h"
#include "Flag.h"

extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;
extern MusicMgr G_MusicMgr;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_Flag = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_Flag = ScreenHeight_Flag / 240; // 缩放倍率

Flag::Flag()
{
    Part = -1;
    loadimage(&OrignImage, "resources/graphics/tile_set.png");
    loadimage(&OrignImage1, "resources/graphics/tile_set.png", 528 * Scale_Flag, 448 * Scale_Flag);
    loadimage(&OrignImage2, "resources/graphics/item_objects.png", 576 * Scale_Flag, 336 * Scale_Flag);
}

void Flag::DrawObject()
{
    if (Part == 0)
    {
        int CropX = 103;  // 裁剪区域左上角x坐标
        int CropY = 80;      // 裁剪区域左上角y坐标
        int CropWidth = 2; // 裁剪区域宽度
        int CropHeight = 16; // 裁剪区域高度

        putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
    }
    else if (Part == 1)
    {
        int CropX = 228 * Scale_Flag;  // 裁剪区域左上角x坐标
        int CropY = 24 * Scale_Flag;      // 裁剪区域左上角y坐标
        int CropWidth = 8 * Scale_Flag; // 裁剪区域宽度
        int CropHeight = 7 * Scale_Flag; // 裁剪区域高度

        DrawImg(CurrentXPosition * Scale_Flag, CurrentYPosition * Scale_Flag, CropWidth, CropHeight, &OrignImage1, CropX, CropY); // 绘制图像
    }
    else if (Part == 2)
    {
        int CropX = 128 * Scale_Flag;  // 裁剪区域左上角x坐标
        int CropY = 32 * Scale_Flag;      // 裁剪区域左上角y坐标
        int CropWidth = 16 * Scale_Flag; // 裁剪区域宽度
        int CropHeight = 16 * Scale_Flag; // 裁剪区域高度

        DrawImg(CurrentXPosition * Scale_Flag, CurrentYPosition * Scale_Flag, CropWidth, CropHeight, &OrignImage2, CropX, CropY); // 绘制图像
    }
}

void Flag::InitCollider()
{
    if (Part == 0)
    {
        BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
        BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 1;
        BoxCollider.ColliderPosition_Top = YPosition;
        BoxCollider.ColliderPosition_Button = YPosition + 7;
    }
}

int Flag::GetPart()
{
    return Part;
}

void Flag::SetPart(int InputPart)
{
    Part = InputPart;
}


// 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
void Flag::OnCollitionEnter()
{
    OnCollitionEnterWithPlayer();
}

// 与玩家重叠时调用的函数
void Flag::OnCollitionEnterWithPlayer()
{

}

void Flag::Animator()
{
    Animation_Descend();
}

void Flag::Animation_Descend()
{
    if (SAnimation_Descend.IsPlayingDescendMusic == 1)
    {
        G_MusicMgr.Play_FlagPole();
        G_MusicMgr.CloseBackgroundMusic();
    }

    if (Part == 2)
    {
        if (P_PlayerMario.EventsDispatcher_PlayerMario.GetIsFlagPulling() == true)
        {
            SAnimation_Descend.IsPlayingDescendMusic++;
            if (YPosition <= 184)
            {
                YPosition += 2;
            }
            else
            {
                YPosition = 185;
                if (SAnimation_Descend.MusicStageClearHavePlayed == false)
                {
                    G_MusicMgr.Stage_Clear();
                    SAnimation_Descend.MusicStageClearHavePlayed = true;
                }
                P_PlayerMario.EventsDispatcher_PlayerMario.SetIsFlagPulling(false);
            }
        }
    }
}

void Flag::Update()
{
    SetCurrentPosition();
    InitCollider();
    OnCollitionEnter();
    Animator();
}