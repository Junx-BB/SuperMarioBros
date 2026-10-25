#include "stdafx.h"
#include "Hill.h"

extern Camera G_Camera;

Hill::Hill()
{
    loadimage(&OrignImage, "resources/graphics/level_1.png");
}

void Hill::DrawObject()
{
    int CropX = 0; // 裁剪区域左上角x坐标
    int CropY = 165; // 裁剪区域左上角y坐标
    int CropWidth = 80; // 裁剪区域宽度
    int CropHeight = 35; // 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

void Hill::Update()
{
    SetCurrentPosition();
}