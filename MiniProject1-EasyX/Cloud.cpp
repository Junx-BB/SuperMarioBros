#include "stdafx.h"
#include "Cloud.h"

extern GameMgr G_GameMgr;
extern Camera G_Camera;

Cloud::Cloud()
{
    loadimage(&OrignImage, "resources/graphics/level_1.png");
    CutXPosition = 0;
    CutWidth = 0;
}

void Cloud::DrawObject(int XPosition, int Width)
{
    int CropX = 139 + XPosition; // 裁剪区域左上角x坐标
    int CropY = 42; // 裁剪区域左上角y坐标
    int CropWidth = Width; // 裁剪区域宽度
    int CropHeight = 24; // 裁剪区域高度

    putimage(CurrentXPosition, CurrentYPosition, CropWidth, CropHeight, &OrignImage, CropX, CropY); // 绘制图像
}

int Cloud::GetCutXPosition()
{
    return CutXPosition;
}

int Cloud::GetCutWidth()
{
    return CutWidth;
}

void Cloud::SetCutParameters(int InputCutXPosition = 139, int InputCutWidth = 32)
{
    CutXPosition = InputCutXPosition;
    CutWidth = InputCutWidth;
}

void Cloud::Update()
{
    SetCurrentPosition();
}