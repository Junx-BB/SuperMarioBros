#include "stdafx.h"
#include "PlayerMgr.h"

PlayerMgr::PlayerMgr()
{
	Player = -1;
}

void PlayerMgr::Update()
{
	if (Player == E_GAME_LEVEL_PLAYER_MARIO)
	{
		PlayerMario.Update();
	}
}

void PlayerMgr::Render()
{
	if (Player == E_GAME_LEVEL_PLAYER_MARIO)
	{
		PlayerMario.Render();
	}
}
