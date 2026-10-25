#include "stdafx.h"
#include "EnemyGoomba.h"


extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_Goomba = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_Goomba = ScreenHeight_Goomba / 240;// 缩放倍率

EnemyGoomba::EnemyGoomba(int XPosition, int YPosition, double XSpeed, double YSpeed, int direction, int Tag, int step_num, int frames, int f_speed, int index) :
	EnemyBase(XPosition, YPosition, XSpeed, YSpeed, direction, Tag, step_num, frames, f_speed, index)
{
	T_Fall = 0;
	T_Down = 0;
}

void EnemyGoomba::InitCollider()
{
	BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
	BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 17;
	BoxCollider.ColliderPosition_Top = YPosition;
	BoxCollider.ColliderPosition_Button = YPosition + 15;
}

//移动
void EnemyGoomba::Move()
{
	if (direction == 0)
	{
		XPosition -= XSpeed;
	}
	else
	{
		XPosition += XSpeed;
	}
}

//改变方向
void EnemyGoomba::ChangeDirection()
{
	if (OnEnterColliderLeftWithTag_1() || OnEnterColliderRightWithTag_1())
	{
		direction = (direction + 1) % 2;
	}
}

//掉落
void EnemyGoomba::FallDown()
{
	if (IsNearTopWithTag_1() == false && OnEnterColliderLeftWithTag_1() == false && OnEnterColliderRightWithTag_1() == false && OnEnterColliderTopWithTag_1() == false && OnEnterColliderButtonWithTag_1() == false)
	{
		YSpeed += 0.5;
		YPosition += static_cast<int>(YSpeed);
	}
	else
	{
		YSpeed = 0;
	}
	while (OnEnterColliderTopWithTag_1() == true)
	{
		YPosition--;
		InitCollider();
	}
}

//判断是否被踩
bool EnemyGoomba::JudgeStep()
{
	bool Step = false;
	if ((BoxCollider.ColliderPosition_Right - P_PlayerMario.BoxCollider.ColliderPosition_Left) * (BoxCollider.ColliderPosition_Left - P_PlayerMario.BoxCollider.ColliderPosition_Right) <= 0)
	{
		if ((BoxCollider.ColliderPosition_Top - P_PlayerMario.BoxCollider.ColliderPosition_Button) * (BoxCollider.ColliderPosition_Top + 5 - P_PlayerMario.BoxCollider.ColliderPosition_Button) <= 0)
		{
			Step = true;
		}
	}
	return Step;
}

//被踩
void EnemyGoomba::BeStepped()
{
	if (JudgeStep())
	{
		step_num++;
		YPosition += 8;
	}
}

//判断是否被顶
bool EnemyGoomba::BrickFloat()
{
	bool Head = false;
	auto& Bricks = G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks;
	for (int i = 0; i < Bricks.size(); i++)
	{
		if (Bricks[i].SAnimation_Floating.IsFloating && (Bricks[i].BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Bricks[i].BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) < 0)
		{
			Head = true;
		}
	}
	return false;
}

//被顶
void EnemyGoomba::BeHeaded()
{
	if (BrickFloat())
	{
		if (P_PlayerMario.GetDirection() == 1)
		{
			direction = 1;
		}
		else if (P_PlayerMario.GetDirection() == -1)
		{
			direction = 0;
		}
		step_num = 3;
	}
}

//死亡
void EnemyGoomba::Die()
{
	YPosition = YPosition - 3 * T_Fall + (0.5 * 1 * T_Fall * T_Fall);
	T_Fall++;
}

void EnemyGoomba::Update()
{
	//更新实际位置
	SetCurrentPosition();

	//更新碰撞箱
	InitCollider();

	if (step_num == 0)
	{
		//发生碰撞改变移动方向
		ChangeDirection();

		//掉落
		FallDown();

		//被踩
		BeStepped();

		//被撞
		BeCrashed_KoopaTroopa();

		//被顶
		BeHeaded();

		//左右移动
		Move();
	}
	else if (step_num == 1)
	{
		T_Down++;
		if (T_Down == 6)
		{
			YPosition = 350;
		}
	}
	else if (step_num == 3)
	{
		//死亡
		Die();

		//左右移动
		Move();
	}
}

void EnemyGoomba::Render()
{
	if (step_num == 0)
	{
		DrawImg(CurrentXPosition * Scale_Goomba, CurrentYPosition * Scale_Goomba, 17 * Scale_Goomba, 16 * Scale_Goomba, &img_Enemy, (158 + index * 18) * Scale_Goomba, 0 * Scale_Goomba);
	}
	else if (step_num == 1)
	{
		DrawImg(CurrentXPosition * Scale_Goomba, CurrentYPosition * Scale_Goomba, 17 * Scale_Goomba, 8 * Scale_Goomba, &img_Enemy, 194 * Scale_Goomba, 0 * Scale_Goomba);
	}
	else if (step_num == 3)
	{
		DrawImg(CurrentXPosition * Scale_Goomba, CurrentYPosition * Scale_Goomba, 17 * Scale_Goomba, 16 * Scale_Goomba, &img_Enemy, 212 * Scale_Goomba, 0 * Scale_Goomba);
	}

	if (JudgeStep() || BrickFloat() || JudgeCrash())
	{
		IsDrawText = true;
		TextXPosition = CurrentXPosition;
		TextYPosition = CurrentYPosition;
	}
	if (IsDrawText)
	{
		settextstyle(8, 0, _T("FixedsysTTF"));
		setbkmode(TRANSPARENT);
		outtextxy(TextXPosition, TextYPosition - TextPosition, _T("100"));
		TextPosition++;
		if (TextPosition > 50)
		{
			IsDrawText = false;
			TextPosition = 10;
		}
	}

	index = (GetTickCount64() / f_speed % frames);
	frameTime = GetTickCount64() - frameStart;
}