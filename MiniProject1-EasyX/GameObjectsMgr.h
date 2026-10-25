#pragma once
#include <vector>
#include "GroundBrick.h"
#include "Cloud.h"
#include "Bush.h"
#include "Brick.h"
#include "LuckyBrick.h"
#include "EmptyLuckyBrick.h"    
#include "HardBrick.h"
#include "Hill.h"
#include "SmallHill.h"
#include "PipeTop.h"
#include "PipeBody.h"
#include "Castle.h"
#include "Flag.h"
#include "GrowMushroom.h"
#include "Coin.h"
#include "FireFlower.h"

using namespace std;


class GameObjectsMgr
{
private:
	int CollitionIndex_PlayerToBlock; // 与玩家重叠的砖块的索引
public:
	GameObjectsMgr();
	void Update();
	void Render();
	void DrawObjects();
	void AddGroundBrick(int InputXPosition, int InputYPosition);
	void AddCloud(int InputXPosition, int InputYPosition, int CutXPosition = 0, int CutWidth = 32);
	void AddBush(int InputXPosition, int InputYPosition, int CutXPosition = 0, int CutWidth = 32);
	void AddBrick(int InputXPosition, int InputYPosition, int InputType = 0);
	void AddLuckyBrick(int InputXPosition, int InputYPosition, int  InputType = 0);
	void AddEmptyLuckyBrick(int InputXPosition, int InputYPosition);
	void AddHardBrick(int InputXPosition, int InputYPosition);
	void AddHill(int InputXPosition, int InputYPosition);
	void AddSmallHill(int InputXPosition, int InputYPosition);
	void AddPipeTop(int InputXPosition, int InputYPosition);
	void AddPipeBody(int InputXPosition, int InputYPosition);
	void AddCastle(int InputXPosition, int InputYPosition);
	void AddFlag(int InputXPosition, int InputYPosition, int InputPart = 0);
	void AddGrowMushroom(int InputXPosition, int InputYPosition);
	void AddCoin(int InputXPosition, int InputYPosition,int InputType = 0);
	void AddFireFlower(int InputXPosition, int InputYPosition);
	void ClearAllObjects();
	void ObjectReserve();
	int GetCollitionIndex_PlayerToBlock(); // 获取与玩家重叠的砖块的索引
	void SetCollitionIndex_PlayerToBlock(int InputIndex); // 设置与玩家重叠的砖块的索引

	vector<GroundBrick> vecGroundBricks; // 地面砖块容器
	vector<Cloud> vecClouds; // 云容器
	vector<Bush> vecBushes; // 灌木丛容器
	vector<Brick> vecBricks; // 砖块容器
	vector<LuckyBrick> vecLuckyBricks; // 问号砖块容器
	vector<EmptyLuckyBrick> vecEmptyLuckyBricks; // 空问号砖块容器
	vector<HardBrick> vecHardBricks; // 硬砖块容器
	vector<Hill> vecHills; // 山容器
	vector<SmallHill> vecSmallHills; // 小山容器
	vector<PipeTop> vecPipeTops; // 管道头容器
	vector<PipeBody> vecPipeBodys; // 管道体容器
	vector<Castle> vecCastles; // 城堡容器
	vector<Flag> vecFlags; // 旗子容器

	vector<GrowMushroom> vecGrowMushrooms; // 红蘑菇容器
	vector<Coin> vecCoins; // 金币容器
	vector<FireFlower> vecFireFlowers; // 火焰花容器
};


