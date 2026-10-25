#pragma once
#include "PlayerMario.h"

class PlayerMgr
{
private:
	PlayerMario PlayerMario;
	enum
	{
		E_GAME_LEVEL_PLAYER_MARIO
	};
	int Player;
public:
	PlayerMgr();
	void Update();
	void Render();
};

