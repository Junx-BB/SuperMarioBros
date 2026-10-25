#pragma once
#include "Prop.h"

class Coin : public Prop
{
private:
	int Type;
public:
	Coin();
	void DrawObject();
	void SetType(int InputType);
	virtual void SetPosition(int InputXPosition, int InputYPosition);
	void Animator(); // 动画器
	void Animaiton_Fall();
	void Animation_Spin();
	void HaveDoneAnimation_Fall(); // 金币下落动画执行完毕后执行的函数
	void Update();

	// 金币下落动画结构体
	struct SAnimation_Fall
	{
		float Float_YPosition; // 金币初始y轴坐标
		float Gravity = 625;
		float InitialYSpeed = -250; // 金币初始竖直初速度
		int InitialYPosition; // 金币初始y轴坐标
	};
	SAnimation_Fall SAnimation_Fall;

	// 金币旋转动画结构体
	struct SAnimation_Spin
	{
		int CutXPosition = 0; // 图片裁剪的x轴位置
	};
	SAnimation_Spin SAnimation_Spin;
};