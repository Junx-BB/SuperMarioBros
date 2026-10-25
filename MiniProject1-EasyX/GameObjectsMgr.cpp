#include "stdafx.h"
#include "GameObjectsMgr.h"

GameObjectsMgr::GameObjectsMgr()
{
    ObjectReserve();
    CollitionIndex_PlayerToBlock = -1;
}

void GameObjectsMgr::Update()
{
    // 场景物体
    for (int i = 0; i < vecGroundBricks.size(); i++)
    {
        vecGroundBricks[i].Update();
    }
    for (int i = 0; i < vecClouds.size(); i++)
    {
        vecClouds[i].Update();
    }
    for (int i = 0; i < vecBushes.size(); i++)
    {
        vecBushes[i].Update();
    }
    for (int i = 0; i < vecBricks.size(); i++)
    {
        vecBricks[i].Update();
    }
    for (int i = 0; i < vecLuckyBricks.size(); i++)
    {
        vecLuckyBricks[i].Update();
    }
    for (int i = 0; i < vecEmptyLuckyBricks.size(); i++)
    {
        vecEmptyLuckyBricks[i].Update();
    }
    for (int i = 0; i < vecHardBricks.size(); i++)
    {
        vecHardBricks[i].Update();
    }
    for (int i = 0; i < vecHills.size(); i++)
    {
        vecHills[i].Update();
    }
    for (int i = 0; i < vecSmallHills.size(); i++)
    {
        vecSmallHills[i].Update();
    }
    for (int i = 0; i < vecPipeTops.size(); i++)
    {
        vecPipeTops[i].Update();
    }
    for (int i = 0; i < vecPipeBodys.size(); i++)
    {
        vecPipeBodys[i].Update();
    }
    for (int i = 0; i < vecCastles.size(); i++)
    {
        vecCastles[i].Update();
    }
    for (int i = 0; i < vecFlags.size(); i++)
    {
        vecFlags[i].Update();
    }

    // 道具
    for (int i = 0; i < vecGrowMushrooms.size(); i++)
    {
        vecGrowMushrooms[i].Update();
    }
    for (int i = 0; i < vecCoins.size(); i++)
    {
        vecCoins[i].Update();
    }
    for (int i = 0; i < vecFireFlowers.size(); i++)
    {
        vecFireFlowers[i].Update();
    }
}

void GameObjectsMgr::Render()
{
    DrawObjects();
}

void GameObjectsMgr::DrawObjects()
{
    // 场景物体
    for (int i = 0; i < vecGroundBricks.size(); i++)
    {
        vecGroundBricks[i].DrawObject();
    }
    for (int i = 0; i < vecClouds.size(); i++)
    {
        vecClouds[i].DrawObject(vecClouds[i].GetCutXPosition(), vecClouds[i].GetCutWidth());
    }
    for (int i = 0; i < vecBushes.size(); i++)
    {
        vecBushes[i].DrawObject(vecBushes[i].GetCutXPosition(), vecBushes[i].GetCutWidth());
    }
    for (int i = 0; i < vecBricks.size(); i++)
    {
        vecBricks[i].DrawObject();
    }
    for (int i = 0; i < vecLuckyBricks.size(); i++)
    {
        vecLuckyBricks[i].DrawObject();
    }
    for (int i = 0; i < vecEmptyLuckyBricks.size(); i++)
    {
        vecEmptyLuckyBricks[i].DrawObject();
    }
    for (int i = 0; i < vecHardBricks.size(); i++)
    {
        vecHardBricks[i].DrawObject();
    }
    for (int i = 0; i < vecHills.size(); i++)
    {
        vecHills[i].DrawObject();
    }
    for (int i = 0; i < vecSmallHills.size(); i++)
    {
        vecSmallHills[i].DrawObject();
    }
    for (int i = 0; i < vecPipeTops.size(); i++)
    {
        vecPipeTops[i].DrawObject();
    }
    for (int i = 0; i < vecPipeBodys.size(); i++)
    {
        vecPipeBodys[i].DrawObject();
    }
    for (int i = 0; i < vecCastles.size(); i++)
    {
        vecCastles[i].DrawObject();
    }
    for (int i = 0; i < vecFlags.size(); i++)
    {
        vecFlags[i].DrawObject();
    }

    // 道具
    for (int i = 0; i < vecGrowMushrooms.size(); i++)
    {
        vecGrowMushrooms[i].DrawObject();
    }
    for (int i = 0; i < vecCoins.size(); i++)
    {
        vecCoins[i].DrawObject();
    }
    for (int i = 0; i < vecFireFlowers.size(); i++)
    {
        vecFireFlowers[i].DrawObject();
    }
}
 
// 添加场景
void GameObjectsMgr::AddGroundBrick(int InputXPosition, int InputYPosition)
{
    GroundBrick GroundBrick;
    GroundBrick.SetPosition(InputXPosition, InputYPosition);
    vecGroundBricks.push_back(GroundBrick);
}
void GameObjectsMgr::AddCloud(int InputXPosition, int InputYPosition,int CutXPosition,int CutWidth)
{
    Cloud Cloud;
    Cloud.SetPosition(InputXPosition, InputYPosition);
    Cloud.SetCutParameters(CutXPosition, CutWidth);
    vecClouds.push_back(Cloud);
}
void GameObjectsMgr::AddBush(int InputXPosition, int InputYPosition, int CutXPosition, int CutWidth)
{
    Bush Bush;
    Bush.SetPosition(InputXPosition, InputYPosition);
    Bush.SetCutParameters(CutXPosition, CutWidth);
    vecBushes.push_back(Bush);
}
void GameObjectsMgr::AddBrick(int InputXPosition, int InputYPosition, int InputType)
{
    Brick Brick;
    Brick.SetPosition(InputXPosition, InputYPosition);
    vecBricks.push_back(Brick);
}
void GameObjectsMgr::AddLuckyBrick(int InputXPosition, int InputYPosition,int InputType)
{
    LuckyBrick LuckyBrick;
    LuckyBrick.SetPosition(InputXPosition, InputYPosition);
    LuckyBrick.SetType(InputType);
    vecLuckyBricks.push_back(LuckyBrick);
}
void GameObjectsMgr::AddEmptyLuckyBrick(int InputXPosition, int InputYPosition)
{
    LuckyBrick LuckyBrick;
    LuckyBrick.SetPosition(InputXPosition, InputYPosition);
    vecLuckyBricks.push_back(LuckyBrick);
}
void GameObjectsMgr::AddHardBrick(int InputXPosition, int InputYPosition)
{
    HardBrick HardBrick;
    HardBrick.SetPosition(InputXPosition, InputYPosition);
    vecHardBricks.push_back(HardBrick);
}
void GameObjectsMgr::AddHill(int InputXPosition, int InputYPosition)
{
    Hill Hill;
    Hill.SetPosition(InputXPosition, InputYPosition);
    vecHills.push_back(Hill);
}
void GameObjectsMgr::AddSmallHill(int InputXPosition, int InputYPosition)
{
    SmallHill SmallHill;
    SmallHill.SetPosition(InputXPosition, InputYPosition);
    vecSmallHills.push_back(SmallHill);
}
void GameObjectsMgr::AddPipeTop(int InputXPosition, int InputYPosition)
{
    PipeTop PipeTop;
    PipeTop.SetPosition(InputXPosition, InputYPosition);
    vecPipeTops.push_back(PipeTop);
}
void GameObjectsMgr::AddPipeBody(int InputXPosition, int InputYPosition)
{
    PipeBody PipeBody;
    PipeBody.SetPosition(InputXPosition, InputYPosition);
    vecPipeBodys.push_back(PipeBody);
}
void GameObjectsMgr::AddCastle(int InputXPosition, int InputYPosition)
{
    Castle Castle;
    Castle.SetPosition(InputXPosition, InputYPosition);
    vecCastles.push_back(Castle);
}
void GameObjectsMgr::AddFlag(int InputXPosition, int InputYPosition ,int InputPart)
{
    Flag Flag;
    Flag.SetPosition(InputXPosition, InputYPosition);
    Flag.SetPart(InputPart);
    vecFlags.push_back(Flag);
}

// 添加道具
void GameObjectsMgr::AddGrowMushroom(int InputXPosition, int InputYPosition)
{
    GrowMushroom GrowMushroom;
    GrowMushroom.SetPosition(InputXPosition, InputYPosition);
    vecGrowMushrooms.push_back(GrowMushroom);
}
void GameObjectsMgr::AddCoin(int InputXPosition, int InputYPosition, int InputType)
{
    Coin Coin;
    Coin.SetPosition(InputXPosition, InputYPosition);
    Coin.SetType(InputType);
    vecCoins.push_back(Coin);
}

void GameObjectsMgr::AddFireFlower(int InputXPosition, int InputYPosition)
{
    FireFlower FireFlower;
    FireFlower.SetPosition(InputXPosition, InputYPosition);
    vecFireFlowers.push_back(FireFlower);
}

void GameObjectsMgr::ClearAllObjects()
{
    // 场景物体

    for (int i = 0; i < vecGroundBricks.size(); i++)
    {
        vecGroundBricks.erase(vecGroundBricks.begin() + 1);
    }
    for (int i = 0; i < vecClouds.size(); i++)
    {
        vecClouds.erase(vecClouds.begin() + 1);
    }
    for (int i = 0; i < vecBushes.size(); i++)
    {
        vecBushes.erase(vecBushes.begin() + 1);
    }
    for (int i = 0; i < vecBricks.size(); i++)
    {
        vecBricks.erase(vecBricks.begin() + 1);
    }
    for (int i = 0; i < vecLuckyBricks.size(); i++)
    {
        vecLuckyBricks.erase(vecLuckyBricks.begin() + 1);
    }
    for (int i = 0; i < vecEmptyLuckyBricks.size(); i++)
    {
        vecEmptyLuckyBricks.erase(vecEmptyLuckyBricks.begin() + 1);
    }
    for (int i = 0; i < vecHardBricks.size(); i++)
    {
        vecHardBricks.erase(vecHardBricks.begin() + 1);
    }
    for (int i = 0; i < vecHills.size(); i++)
    {
        vecHills.erase(vecHills.begin() + 1);
    }
    for (int i = 0; i < vecSmallHills.size(); i++)
    {
        vecSmallHills.erase(vecSmallHills.begin() + 1);
    }
    for (int i = 0; i < vecPipeTops.size(); i++)
    {
        vecPipeTops.erase(vecPipeTops.begin() + 1);
    }
    for (int i = 0; i < vecPipeBodys.size(); i++)
    {
        vecPipeBodys.erase(vecPipeBodys.begin() + 1);
    }
    for (int i = 0; i < vecFlags.size(); i++)
    {
        vecFlags.erase(vecFlags.begin() + 1);
    }

    // 道具
    for (int i = 0; i < vecGrowMushrooms.size(); i++)
    {
        vecGrowMushrooms.erase(vecGrowMushrooms.begin() + 1);
    }
    for (int i = 0; i < vecCoins.size(); i++)
    {
        vecCoins.erase(vecCoins.begin() + 1);
    }
    for (int i = 0; i < vecFireFlowers.size(); i++)
    {
        vecFireFlowers.erase(vecFireFlowers.begin() + 1);
    }
}

void GameObjectsMgr::ObjectReserve()
{
    vecGroundBricks.reserve(vecGroundBricks.size() + 161);
    vecClouds.reserve(vecClouds.size() + 20);
    vecBushes.reserve(vecBushes.size() + 20);
    vecBricks.reserve(vecBricks.size() + 22);
    vecLuckyBricks.reserve(vecLuckyBricks.size() + 15);
    vecHardBricks.reserve(vecHardBricks.size() + 57);
    vecHills.reserve(vecHills.size() + 5);
    vecSmallHills.reserve(vecSmallHills.size() + 5);
    vecPipeTops.reserve(vecPipeTops.size() + 5);
    vecPipeBodys.reserve(vecPipeBodys.size() + 5);
    vecCastles.reserve(vecCastles.size() + 1);
    vecFlags.reserve(vecFlags.size() + 10);
}

int GameObjectsMgr::GetCollitionIndex_PlayerToBlock()
{
    return CollitionIndex_PlayerToBlock;
}

void GameObjectsMgr::SetCollitionIndex_PlayerToBlock(int InputIndex)
{
    CollitionIndex_PlayerToBlock = InputIndex;
}
