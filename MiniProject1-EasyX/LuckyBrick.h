#pragma once
#include "Block.h"

class LuckyBrick : public Block
{
private:
	int Tag;
	int Type;
	bool IsEmpty;
	bool IsEnterColliderWithPlayer_Top;
public:
	LuckyBrick();
	void DrawObject();
	virtual void InitCollider();
	void SetType(int InputType);
	int GetTag();
	bool GetIsEnterColliderWithPlayer_Top();
	void SetIsEnterColliderWithPlayer_Top(bool State = true);
	void OnCollitionEnter(); // 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
	void OnCollitionEnterWithPlayer_Top(); // 与玩家在其上方重叠时调用的函数
	void InitAnimation_Floating(); //初始化动画：起伏
	void Animator(); // 动画器
	void Animation_Floating(); // 动画：浮动
	void Update();

	// 浮动动画结构体
	struct SAnimation_Floating
	{
		bool IsFloating = false; // 砖块是否在浮动
		float Float_YPosition = 0; // float类型的y轴坐标
		float InitialSpeed = -4; // 砖块运动初速度
		float CurrentSpeed = 0; // 砖块运动当前速度
		float Acceleration = 10; // 砖块运动加速度
		int DrawOffset_Y = 0; // 砖块渲染的y轴方向偏移量
	};
	SAnimation_Floating SAnimation_Floating;
};

