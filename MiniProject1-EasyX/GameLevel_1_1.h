#pragma once
#include "GameObjectsMgr.h"
#include "EnemyMgr.h"

class GameLevel_1_1
{
private:

public:
	GameLevel_1_1();
	void Init();
	void ShowInformations();
	void Update();
	void Render();

	EnemyMgr EnemyMgr;
};

