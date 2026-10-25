#include "stdafx.h"
#include "HardBrick.h"

extern Camera G_Camera;

HardBrick::HardBrick()
{
    Tag = 1;
    loadimage(&OrignImage, "resources/graphics/tile_set.png");
}

void HardBrick::DrawObject()
{
    int CropX = 0;     // 裁剪区域左上角x坐标
    int CropY = 16;      // 裁剪区域左上角y坐标
    int CropWidth = 16; // 裁剪区域宽度
    int CropHeight = 16;// 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void HardBrick::InitCollider()
{
    BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
    BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 15;
    BoxCollider.ColliderPosition_Top = YPosition;
    BoxCollider.ColliderPosition_Button = YPosition + 15;
}

int HardBrick::GetTag()
{
    return Tag;
}

bool HardBrick::CheckCollisionWithTag_0()
{
    return false;
}

void HardBrick::Update()
{
    SetCurrentPosition();
    InitCollider();
}
