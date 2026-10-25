#pragma once
#include <graphics.h>
#include <conio.h>
#include "Block.h"

class Prop
{
protected:
	int XPosition;
	int YPosition;
	int CurrentXPosition;
	int CurrentYPosition;
	bool IsEnterColliderWithPlayer;
	IMAGE OrignImage;
public:
    Prop();
	virtual void SetPosition(int InputXPosition, int InputYPosition);
	virtual void SetCurrentPosition();
	virtual void InitCollider();
	bool GetIsEnterColliderWithPlayer();
	void SetIsEnterColliderWithPlayer(bool State = true);
	bool OnEnterColliderLeftWithTag_1(); // 判断是否与带有标签1的物体在左侧重叠的函数
	bool OnEnterColliderRightWithTag_1(); // 判断是否与带有标签1的物体在右侧重叠的函数
	bool OnEnterColliderTopWithTag_1(); // 判断是否与带有标签1的物体在物体的上方重叠的函数
	bool OnEnterColliderButtonWithTag_1(); // 判断是否与带有标签1的物体在物体的下方重叠的函数
	bool OnEnterColliderWithBlock_Left(Block& Block); // 判断是否与砖块在左侧重叠的函数
	bool OnEnterColliderWithBlock_Right(Block& Block); // 判断是否与砖块在右侧重叠的函数
	bool OnEnterColliderWithBlock_Top(Block& Block); // 判断是否与砖块在物体的上方重叠的函数
	bool OnEnterColliderWithBlock_Button(Block& Block); // 判断是否与砖块在物体的下方重叠的函数
	bool IsNearLeftWithTag_1(); // 判断是否贴着标签为1的物体左侧的函数
	bool IsNearRightWithTag_1(); // 判断是否贴着标签为1的物体上侧的函数
	bool IsNearTopWithTag_1(); // 判断是否贴着标签为1的物体下侧的函数
	bool IsNearButtonWithTag_1(); // 判断是否贴着标签为1的物体右侧的函数
	bool IsNearBlock_Left(Block& Block); // 判断是否贴着方块左侧的函数
	bool IsNearBlock_Right(Block& Block); // 判断是否贴着方块右侧的函数
	bool IsNearBlock_Top(Block& Block); // 判断是否贴着方块上侧的函数
	bool IsNearBlock_Button(Block& Block); // 判断是否贴着方块下侧的函数

	struct BoxCollider
	{
		int ColliderPosition_Left;
		int ColliderPosition_Right;
		int ColliderPosition_Top;
		int ColliderPosition_Button;
	};
	BoxCollider BoxCollider;
};

