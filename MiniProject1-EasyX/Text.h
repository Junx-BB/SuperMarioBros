#pragma once

class Text
{
private:
	int Type; // 字体的类型，0为悬浮字体，1为静止字体
	int XPosition;
	int YPosition;
	int CurrentYPosition; // 文字当前的y轴坐标
	string Content; // 文字的内容
public:
	Text();
	void Init(int InputXPosition, int InputYposition, string InputText);
	void Update();
	void Render();
};