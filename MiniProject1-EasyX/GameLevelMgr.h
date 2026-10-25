#pragma once
#include "GameLevel_1_1.h"
#include "PlayerMario.h"

class GameLevelMgr
{
private:
	enum
	{
		E_GAME_LEVEL_1_1
	};
	int Level;
public:
	GameLevelMgr();
	void Update();
	void Render();

	GameObjectsMgr GameObjectsMgr;
	GameLevel_1_1 GameLevel_1_1;
};

