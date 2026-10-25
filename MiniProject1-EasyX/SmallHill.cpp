#include "stdafx.h"
#include "SmallHill.h"

extern Camera G_Camera;

SmallHill::SmallHill()
{
    loadimage(&OrignImage, "resources/graphics/level_1.png");
}


void SmallHill::DrawObject()
{
    int CropX = 256; // 裁剪区域左上角x坐标
    int CropY = 181; // 裁剪区域左上角y坐标
    int CropWidth = 48; // 裁剪区域宽度
    int CropHeight = 19; // 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void SmallHill::Update()
{
    SetCurrentPosition();
}