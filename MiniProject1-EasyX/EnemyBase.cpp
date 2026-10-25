#include "stdafx.h"
#include "EnemyBase.h"
#include "EnemyMgr.h"


extern Camera G_Camera;
extern GameMgr G_GameMgr;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_Enemy = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_Enemy = ScreenHeight_Enemy / 240;// 缩放倍率

EnemyBase::EnemyBase(int XPosition, int YPosition, double XSpeed, double YSpeed, int direction, int Tag, int step_num, int frames, int f_speed, int index) :
	XPosition(XPosition), YPosition(YPosition), CurrentXPosition(XPosition - G_Camera.GetWorldXPosition()), CurrentYPosition(YPosition - G_Camera.GetWorldXPosition()), XSpeed(XSpeed), YSpeed(YSpeed), direction(direction), Tag(Tag), step_num(step_num), frames(frames), f_speed(f_speed), index(index)
{
	loadimage(&img_Enemy, "resources/graphics/mario_bro.png", 512 * Scale_Enemy, 512 * Scale_Enemy);
}

int EnemyBase::GetXPositiion()
{
	return XPosition;
}

int EnemyBase::GetYPosition()
{
	return YPosition;
}

int EnemyBase::GetDirection()
{
	return direction;
}

int EnemyBase::GetTag()
{
	return Tag;
}

int EnemyBase::GetStepNum()
{
	return step_num;
}

void EnemyBase::SetCurrentPosition()
{
	CurrentXPosition = XPosition - G_Camera.GetWorldXPosition();
	CurrentYPosition = YPosition - G_Camera.GetWorldYPosition();
}

bool EnemyBase::JudgeCrash()
{
	bool Crash = false;
	auto& KoopaTroopa = G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas;
	for (int i = 0; i < KoopaTroopa.size(); i++)
	{
		if (KoopaTroopa[i].GetStepNum() == 2)
		{
			if (BoxCollider.ColliderPosition_Right > KoopaTroopa[i].BoxCollider.ColliderPosition_Left && BoxCollider.ColliderPosition_Left < KoopaTroopa[i].BoxCollider.ColliderPosition_Right)
			{
				if ((BoxCollider.ColliderPosition_Top - KoopaTroopa[i].BoxCollider.ColliderPosition_Button) * (BoxCollider.ColliderPosition_Button - KoopaTroopa[i].BoxCollider.ColliderPosition_Top) < 0)
				{
					if (KoopaTroopa[i].GetDirection() == 0)
					{
						direction = 0;
					}
					else if (KoopaTroopa[i].GetDirection() == 1)
					{
						direction = 1;
					}
					Crash = true;
				}
			}
		}
	}
	return Crash;
}

void EnemyBase::BeCrashed_KoopaTroopa()
{
	if (JudgeCrash())
	{
		step_num = 3;
	}
}

// 判断是否与方块重叠的函数

bool EnemyBase::OnEnterColliderWithBlock_Left(Block& Block) // 判断是否与砖块在左侧重叠的函数
{
	bool IsOverlap = false;
	if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) < 0)
	{
		if (Block.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Left > BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Right)
		{
			if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
			{
				IsOverlap = true;
			}
			else if (Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
			{
				IsOverlap = true;
			}
			else
			{
				if (Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) * -1)
				{
					IsOverlap = true;
				}
			}
		}
	}
	return IsOverlap;
}
bool EnemyBase::OnEnterColliderWithBlock_Right(Block& Block) // 判断是否与砖块在右侧重叠的函数
{
	bool IsOverlap = false;
	if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
	{
		if (Block.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Left)
		{
			if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
			{
				IsOverlap = true;
			}
			else if (Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
			{
				IsOverlap = true;
			}
			else
			{
				if (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * -1 && Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top)
				{
					IsOverlap = true;
				}
			}
		}
	}
	return IsOverlap;
}
bool EnemyBase::OnEnterColliderWithBlock_Top(Block& Block) // 判断是否与砖块在物体的上方重叠的函数
{
	bool IsOverlap = false;
	if ((Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
	{
		if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
		{
			if (Block.BoxCollider.ColliderPosition_Left >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right <= BoxCollider.ColliderPosition_Right)
			{
				IsOverlap = true;
			}
			else if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Right)
			{
				IsOverlap = true;
			}
			else
			{
				if (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) * -1)
				{
					IsOverlap = true;
				}
			}
		}
	}
	return IsOverlap;
}
bool EnemyBase::OnEnterColliderWithBlock_Button(Block& Block) // 判断是否与砖块在物体的下方重叠的函数
{
	bool IsOverlap = false;
	if ((Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
	{
		if (Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top)
		{
			if (Block.BoxCollider.ColliderPosition_Left >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right <= BoxCollider.ColliderPosition_Right)
			{
				IsOverlap = true;
			}
			else if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Right)
			{
				IsOverlap = true;
			}
			else
			{
				if (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top > Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top > (BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) * -1)
				{
					IsOverlap = true;
				}
			}
		}
	}
	return IsOverlap;
}

bool EnemyBase::OnEnterColliderLeftWithTag_1() // 判断是否与带有标签1的物体在左侧重叠的函数
{
	bool IsOverlap = false;
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
	{
		if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
		{
			IsOverlap = true;
		}
	}
	return IsOverlap;
}
bool EnemyBase::OnEnterColliderRightWithTag_1() // 判断是否与带有标签1的物体在右侧重叠的函数
{
	bool IsOverlap = false;
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
	{
		if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
		{
			IsOverlap = true;
		}
	}
	return IsOverlap;
}
bool EnemyBase::OnEnterColliderTopWithTag_1() // 判断是否与带有标签1的物体在物体的上方重叠的函数
{
	bool IsOverlap = false;
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
	{
		if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
		{
			IsOverlap = true;
		}
	}
	return IsOverlap;
}
bool EnemyBase::OnEnterColliderButtonWithTag_1() // 判断是否与带有标签1的物体在物体的下方重叠的函数
{
	bool IsOverlap = false;
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
		{
			IsOverlap = true;
			if (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i].SAnimation_Floating.IsFloating == false)
			{
				G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i].SetIsEnterColliderWithPlayer_Top(true);
			}
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
		{
			IsOverlap = true;
			if (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i].SAnimation_Floating.IsFloating == false)
			{
				G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i].SetIsEnterColliderWithPlayer_Top(true);
			}
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
	{
		if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
		{
			IsOverlap = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
	{
		if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
		{
			IsOverlap = true;
		}
	}
	return IsOverlap;
}

bool EnemyBase::IsNearBlock_Top(Block& Block) // 判断是否贴着方块上侧的函数
{
	bool IsNear = false;
	if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Left)
	{
		if (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button == 0 || Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button == 1)
		{
			IsNear = true;
		}
	}
	return IsNear;
}
bool EnemyBase::IsNearTopWithTag_1() // 判断是否贴着标签为1的物体上侧的函数
{
	bool IsNear = false;
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
	{
		if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
		{
			IsNear = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
	{
		if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
		{
			IsNear = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
	{
		if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
		{
			IsNear = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
	{
		if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
		{
			IsNear = true;
		}
	}
	for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
	{
		if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
		{
			IsNear = true;
		}
	}
	return IsNear;
}