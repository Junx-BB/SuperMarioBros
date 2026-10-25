#pragma once
#include "Background.h"

class Bush : public Background
{
private:
	int CutXPosition; // 裁剪的X轴位置
	int CutWidth; // 裁剪的宽度
	IMAGE OrignImage;
public:
	Bush();
	void DrawObject(int XPosition, int Width);
	int GetCutXPosition();
	int GetCutWidth();
	void SetCutParameters(int InputCutXPosition, int InputCutWidth);
	void Update();
};