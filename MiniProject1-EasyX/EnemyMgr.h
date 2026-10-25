#pragma once

#include "stdafx.h"
#include "EnemyGoomba.h"
#include "EnemyKoopaTroopa.h"
#include "EnemyPiranhaPlant.h"

class EnemyMgr
{
private:
	enum
	{
		E_GAME_LEVEL_ENEMY_GOOMBA
	};
public:
	//三个容器储存三种怪
	vector<EnemyGoomba> Goombas;
	vector<EnemyKoopaTroopa> KoopaTroopas;
	vector<EnemyPiranhaPlant> PiranhaPlants;
	EnemyMgr();
	void Update();
	void Render();
};