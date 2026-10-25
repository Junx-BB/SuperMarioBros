#pragma once
#include "EnemyBase.h"

class EnemyPiranhaPlant :public EnemyBase
{
protected:
	int T_Wait;
public:
	EnemyPiranhaPlant(int XPosition = 0, int YPosition = 0, int XSpeed = 0, int YSpeed = 0, int direction = 0, int Tag = 0, int step_num = 0, int T_Wait = 0, int frames = 2, int f_speed = 200, int index = 0);
	void InitCollider();

	void Move();
	void ChangeDirection();
	void Die();

	void Update();
	void Render();
};

