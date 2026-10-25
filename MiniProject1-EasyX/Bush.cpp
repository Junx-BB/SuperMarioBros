#include "stdafx.h"
#include "Bush.h"

extern GameMgr G_GameMgr;
extern Camera G_Camera;

Bush::Bush()
{
    loadimage(&OrignImage, "resources/graphics/level_1.png");
    CutXPosition = 0;
    CutWidth = 0;
}

void Bush::DrawObject(int XPosition, int Width)
{
    int CropX = 376 + XPosition; // 裁剪区域左上角x坐标
    int CropY = 184; // 裁剪区域左上角y坐标
    int CropWidth = Width; // 裁剪区域宽度
    int CropHeight = 16; // 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

int Bush::GetCutXPosition()
{
    return CutXPosition;
}

int Bush::GetCutWidth()
{
    return CutWidth;
}

void Bush::SetCutParameters(int InputCutXPosition, int InputCutWidth)
{
    CutXPosition = InputCutXPosition;
    CutWidth = InputCutWidth;
}

void Bush::Update()
{
    SetCurrentPosition();
}