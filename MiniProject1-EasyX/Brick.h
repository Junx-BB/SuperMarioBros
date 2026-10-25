#pragma once
#include "Block.h"
#include "PlayerMario.h"

class Brick : public Block
{
private:
	int Tag;
	int Type;
	bool IsEnterColliderWithPlayer_Top;
	
public:
	Brick();
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
	void Animation_Floating(); // 动画：起伏
	void Animation_Disappear();
	void Update();

	struct SAnimation_Floating
	{
		bool IsFloating; // 砖块是否在浮动
		int InitialYPosition; // 最初的y轴坐标
		float Float_YPosition; // float类型的y轴坐标
		float InitialSpeed = -4; // 砖块运动初速度
		float CurrentSpeed; // 砖块运动当前速度
		float Acceleration = 10; // 砖块运动加速度
	};
	SAnimation_Floating SAnimation_Floating;

	struct Animation_Disappear
	{

	};
};

