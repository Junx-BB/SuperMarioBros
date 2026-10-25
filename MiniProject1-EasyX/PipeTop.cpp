#include "stdafx.h"
#include "PipeTop.h"

extern Camera G_Camera;

PipeTop::PipeTop()
{
    Tag = 1;
    loadimage(&OrignImage, "resources/graphics/level_1.png");
}

void PipeTop::DrawObject()
{
    int CropX = 448; // 裁剪区域左上角x坐标
    int CropY = 168; // 裁剪区域左上角y坐标
    int CropWidth = 32; // 裁剪区域宽度
    int CropHeight = 16; // 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void PipeTop::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 31;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}

int PipeTop::GetTag()
{
    return Tag;
}

void PipeTop::Update()
{
    SetCurrentPosition();
    InitCollider();
}