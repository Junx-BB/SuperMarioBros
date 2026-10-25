#include "stdafx.h"
#include "PipeBody.h"

extern Camera G_Camera;

PipeBody::PipeBody()
{
    Tag = 0;
    loadimage(&OrignImage, "resources/graphics/level_1.png");
}

void PipeBody::DrawObject()
{
    int CropX = 450;     // 裁剪区域左上角x坐标
    int CropY = 184;      // 裁剪区域左上角y坐标
    int CropWidth = 28; // 裁剪区域宽度
    int CropHeight = 16;// 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void PipeBody::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition() - 2;
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 29;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}

int PipeBody::GetTag()
{
    return Tag;
}

void PipeBody::Update()
{
    SetCurrentPosition();
    InitCollider();
}