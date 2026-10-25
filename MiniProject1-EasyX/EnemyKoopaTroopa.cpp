#include "stdafx.h"
#include "EnemyKoopaTroopa.h"


extern Camera G_Camera;
extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_KoopaTroopa = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_KoopaTroopa = ScreenHeight_KoopaTroopa / 240;// 缩放倍率

EnemyKoopaTroopa::EnemyKoopaTroopa(int XPosition, int YPosition, double XSpeed, double YSpeed, int direction, int Tag, int step_num, int frames, int f_speed, int index) :
	EnemyBase(XPosition, YPosition, XSpeed, YSpeed, direction, Tag, step_num, frames, f_speed, index)
{
	T_Fall = 0;
	T_Die = 0;
	Down = 0;
	T_Recover = 0;
	T_WaitRecover = 0;
}

void EnemyKoopaTroopa::InitCollider()
{
	BoxCollider.ColliderPosition_Left = XPosition - G_Camera.GetWorldXPosition();
	BoxCollider.ColliderPosition_Right = XPosition - G_Camera.GetWorldXPosition() + 17;
	BoxCollider.ColliderPosition_Top = YPosition + 4;
	BoxCollider.ColliderPosition_Button = YPosition + 24;
}

//移动
void EnemyKoopaTroopa::Move()
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
void EnemyKoopaTroopa::ChangeDirection()
{
	if (OnEnterColliderLeftWithTag_1() || OnEnterColliderRightWithTag_1())
	{
		direction = (direction + 1) % 2;
	}
}

//掉落
void EnemyKoopaTroopa::FallDown()
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
}

//判断是否被踩
bool EnemyKoopaTroopa::JudgeStep()
{
	bool Step = false;
	if ((BoxCollider.ColliderPosition_Right - P_PlayerMario.BoxCollider.ColliderPosition_Left) * (BoxCollider.ColliderPosition_Left - P_PlayerMario.BoxCollider.ColliderPosition_Right) <= 0)
	{
		if ((BoxCollider.ColliderPosition_Top - 1 - P_PlayerMario.BoxCollider.ColliderPosition_Button) * (BoxCollider.ColliderPosition_Top + 5 - P_PlayerMario.BoxCollider.ColliderPosition_Button) <= 0)
		{
			Step = true;
		}
	}
	return Step;
}

//被踩
void EnemyKoopaTroopa::BeStepped()
{
	if (JudgeStep())
	{
		step_num++;
		Down++;
		if (Down == 1)
		{
			YPosition += 10;
		}
	}
}

//判断是否被推
bool EnemyKoopaTroopa::JudgePush()
{
	bool Push = false;
	if (BoxCollider.ColliderPosition_Right > P_PlayerMario.BoxCollider.ColliderPosition_Left && BoxCollider.ColliderPosition_Left < P_PlayerMario.BoxCollider.ColliderPosition_Right)
	{
		if ((BoxCollider.ColliderPosition_Top - P_PlayerMario.BoxCollider.ColliderPosition_Button) * (BoxCollider.ColliderPosition_Button - P_PlayerMario.BoxCollider.ColliderPosition_Top) <= 0)
		{
			direction = 1;
			Push = true;
		}
	}
	else if (BoxCollider.ColliderPosition_Left < P_PlayerMario.BoxCollider.ColliderPosition_Right && BoxCollider.ColliderPosition_Right > P_PlayerMario.BoxCollider.ColliderPosition_Left)
	{
		if ((BoxCollider.ColliderPosition_Top - P_PlayerMario.BoxCollider.ColliderPosition_Button) * (BoxCollider.ColliderPosition_Button - P_PlayerMario.BoxCollider.ColliderPosition_Top) <= 0)
		{
			direction = 0;
			Push = true;
		}
	}
	return Push;
}

//被推
void EnemyKoopaTroopa::BePushed()
{
	if (JudgePush())
	{
		step_num++;
		Down++;
		if (Down == 1)
		{
			YPosition += 6;
		}
	}
}

//判断是否被顶
bool EnemyKoopaTroopa::BrickFloat()
{
	bool Head = 0;
	auto& Bricks = G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks;
	for (int i = 0; i < Bricks.size(); i++)
	{
		if (Bricks[i].SAnimation_Floating.IsFloating && (Bricks[i].BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Bricks[i].BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) < 0)
		{
			Head = true;
		}
	}
	return Head;
}

//被顶
void EnemyKoopaTroopa::BeHeaded()
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
void EnemyKoopaTroopa::Die()
{
	YPosition = YPosition - 3 * T_Fall + (0.5 * 1 * T_Fall * T_Fall);
	T_Fall++;
}

void EnemyKoopaTroopa::Update()
{
	//更新实际位置
	SetCurrentPosition();

	//更新碰撞箱
	InitCollider();

	if (step_num == 0)//站立状态
	{
		//发生碰撞改变移动方向
		ChangeDirection();

		//掉落
		FallDown();

		//被踩
		BeStepped();

		//被顶
		BeHeaded();

		//被撞
		BeCrashed_KoopaTroopa();
	}
	else if (step_num == 1)//龟壳状态
	{
		//掉落
		FallDown();

		//被推
		BePushed();

		T_Recover++;
		XSpeed = 0;
		if (T_Recover > 100)
		{
			T_WaitRecover++;
			if (T_WaitRecover > 40)
			{
				YPosition -= 10;
				step_num = 0;
				XSpeed = 1;
				Down = 0;
				T_Recover = 0;
				T_WaitRecover = 0;
			}
		}

	}
	else if (step_num == 2)//龟壳冲击
	{
		BoxCollider.ColliderPosition_Button -= 10;

		//发生碰撞改变移动方向
		ChangeDirection();

		//掉落
		FallDown();

		T_Die++;
		XSpeed = 5;
		if (T_Die > 100)
		{
			step_num = 3;
		}

	}
	else if (step_num == 3)
	{
		Die();
	}

	//左右移动
	Move();
}

void EnemyKoopaTroopa::Render()
{
	if (step_num == 0)//站立状态
	{
		if (direction == 0)
		{
			DrawImg(CurrentXPosition * Scale_KoopaTroopa, CurrentYPosition * Scale_KoopaTroopa, 17 * Scale_KoopaTroopa, 24 * Scale_KoopaTroopa, &img_Enemy, (248 + index * 18) * Scale_KoopaTroopa, 0 * Scale_KoopaTroopa);
		}
		else if (direction == 1)
		{
			DrawImg(CurrentXPosition * Scale_KoopaTroopa, CurrentYPosition * Scale_KoopaTroopa, 17 * Scale_KoopaTroopa, 24 * Scale_KoopaTroopa, &img_Enemy, (284 + index * 18) * Scale_KoopaTroopa, 0 * Scale_KoopaTroopa);
		}
	}
	else if (step_num == 1)//龟壳状态
	{
		if (T_Recover < 100)
		{
			DrawImg(CurrentXPosition * Scale_KoopaTroopa, CurrentYPosition * Scale_KoopaTroopa, 17 * Scale_KoopaTroopa, 14 * Scale_KoopaTroopa, &img_Enemy, 320 * Scale_KoopaTroopa, 0 * Scale_KoopaTroopa);
		}
		else
		{
			DrawImg(CurrentXPosition * Scale_KoopaTroopa, CurrentYPosition * Scale_KoopaTroopa, 17 * Scale_KoopaTroopa, 14 * Scale_KoopaTroopa, &img_Enemy, (320 + 18 * index) * Scale_KoopaTroopa, 1 * Scale_KoopaTroopa);
		}
	}
	else if (step_num == 2)
	{
		DrawImg(CurrentXPosition * Scale_KoopaTroopa, CurrentYPosition * Scale_KoopaTroopa, 17 * Scale_KoopaTroopa, 14 * Scale_KoopaTroopa, &img_Enemy, 320 * Scale_KoopaTroopa, 0 * Scale_KoopaTroopa);
	}
	else if (step_num = 3)
	{
		DrawImg(CurrentXPosition * Scale_KoopaTroopa, CurrentYPosition * Scale_KoopaTroopa, 17 * Scale_KoopaTroopa, 14 * Scale_KoopaTroopa, &img_Enemy, 230 * Scale_KoopaTroopa, 0 * Scale_KoopaTroopa);
	}


	if (JudgeStep() || BrickFloat() || JudgePush())
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