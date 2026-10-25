#include "stdafx.h"
#include "Castle.h"

Castle::Castle()
{
    loadimage(&OrignImage, "resources/graphics/level_1.png");
}

void Castle::DrawObject()
{
    int CropX = 3232;     // 裁剪区域左上角x坐标
    int CropY = 120;      // 裁剪区域左上角y坐标
    int CropWidth = 80; // 裁剪区域宽度
    int CropHeight = 80;// 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void Castle::Update()
{
    SetCurrentPosition();
}