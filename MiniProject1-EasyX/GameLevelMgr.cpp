#include "stdafx.h"
#include "GameLevelMgr.h"

extern PlayerMario P_PlayerMario;

GameLevelMgr::GameLevelMgr()
{
	Level = E_GAME_LEVEL_1_1;
}

void GameLevelMgr::Update()
{
	if (Level == E_GAME_LEVEL_1_1)
	{
		P_PlayerMario.Update();
		GameLevel_1_1.Update();
	}
}

void GameLevelMgr::Render()
{
	if (Level == E_GAME_LEVEL_1_1)
	{
		GameLevel_1_1.Render();
		P_PlayerMario.Render();
	}
}
