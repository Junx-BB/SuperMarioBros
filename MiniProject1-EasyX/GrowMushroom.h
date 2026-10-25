#pragma once
#include "Prop.h"

class GrowMushroom : public Prop
{
private:

public:
	GrowMushroom();
	void DrawObject();
	virtual void SetPosition(int InputXPosition, int InputYPosition);
	virtual void InitCollider();
	void OnCollitionEnter(); // 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
	void OnCollitionEnterWithPlayer(); // 与玩家重叠时调用的函数
	void OnCollitionEnterWithTag_1(); // 与标签为1的物体重叠时调用的函数
	void Animator(); // 动画器
	void Animation_Move();
	void Animation_Emerge();
	void Animaiton_Fall();
	void Update();

	// 蘑菇水平移动动画结构体
	struct SAnimation_Move
	{
		float AccumulativeXPosition = 0; // 累计的XPosition增量
		float InitialXPosition = 0; // 初始的X轴坐标
		int Ditection = 1; // -1为左，1为右
		float XSpeed = 1.5; // 蘑菇水平移动速度
	};
	SAnimation_Move SAnimation_Move;

	// 蘑菇出现动画结构体
	struct SAnimation_Emerge
	{
		bool IsEmerging = true; // 蘑菇是否正在出现
		float CutOffset_Y = 16; // 图像裁剪y轴位置偏移量
		float Timer = 0; // 对象从创建开始到现在经过的时间
	};
	SAnimation_Emerge SAnimation_Emerge;

	// 蘑菇下落动画结构体
	struct SAnimation_Fall
	{
		float Gravity = 10;
		float CurrentYSpeed = 0; // 蘑菇当前竖直移动速度
		bool OnGround = true; // 判断物体是否在地上
	};
	SAnimation_Fall SAnimation_Fall;
};

