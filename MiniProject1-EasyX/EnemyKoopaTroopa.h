#pragma once
#include "EnemyBase.h"

class EnemyKoopaTroopa :public EnemyBase
{
protected:
	int T_Fall;
	int T_Die;
	int Down;
	int T_Recover;
	int T_WaitRecover;
public:
	EnemyKoopaTroopa(int XPosition = 0, int YPosition = 0, double XSpeed = 0, double YSpeed = 0, int direction = 0, int Tag = 0, int step_num = 0, int frames = 2, int f_speed = 200, int index = 0);
	void InitCollider();

	void Move();
	void ChangeDirection();
	void FallDown();
	bool JudgeStep();
	void BeStepped();
	bool JudgePush();
	void BePushed();
	bool BrickFloat();
	void BeHeaded();
	void Die();

	void Update();
	void Render();
};

