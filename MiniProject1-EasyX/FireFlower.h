#pragma once
#include "Prop.h"

class FireFlower : public Prop
{
private:

public:
	FireFlower();
	void DrawObject();
	virtual void SetPosition(int InputXPosition, int InputYPosition);
	virtual void InitCollider();
	void OnCollitionEnter(); // 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
	void OnCollitionEnterWithPlayer(); // 与玩家重叠时调用的函数
	void Animator(); // 动画器
	void Animation_Emerge();
	void Animation_Blink();
	void Update();

	// 火焰花出现动画结构体
	struct SAnimation_Emerge
	{
		bool IsEmerging = true; // 火焰花是否正在出现
		float CutOffset_Y = 16; // 图像裁剪y轴位置偏移量
		float Timer = 0; // 对象从创建开始到现在经过的时间
	};
	SAnimation_Emerge SAnimation_Emerge;

	// 火焰花出现动画结构体
	struct SAnimation_Blink
	{
		int CutOffset_X = 0; // 图像裁剪的x轴偏移量
	};
	SAnimation_Blink SAnimation_Blink;
};

