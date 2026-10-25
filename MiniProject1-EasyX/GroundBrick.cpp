#include "stdafx.h"
#include "GroundBrick.h"

extern Camera G_Camera;

GroundBrick::GroundBrick()
{
    Tag = 1;
    loadimage(&OrignImage, "resources/graphics/tile_set.png");
}

void GroundBrick::DrawObject()
{
    int CropX = 0;     // 裁剪区域左上角x坐标
    int CropY = 0;      // 裁剪区域左上角y坐标
    int CropWidth = 16; // 裁剪区域宽度
    int CropHeight = 16;// 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void GroundBrick::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 15;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}


int GroundBrick::GetTag()
{
    return Tag;
}

void GroundBrick::Update()
{
    SetCurrentPosition();
    InitCollider();
}