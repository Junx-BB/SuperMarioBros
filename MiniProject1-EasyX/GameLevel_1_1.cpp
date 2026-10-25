#include "stdafx.h"
#include "GameLevel_1_1.h"

extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;
extern MusicMgr G_MusicMgr;

GameLevel_1_1::GameLevel_1_1()
{
	Init();
}

void GameLevel_1_1::Update()
{
	G_GameMgr.GameLevelMgr.GameObjectsMgr.Update();
	EnemyMgr.Update();
}

void GameLevel_1_1::Render()
{
	G_GameMgr.GameLevelMgr.GameObjectsMgr.Render();
	EnemyMgr.Render();
	ShowInformations();
	setbkcolor(RGB(107, 140, 255)); // 设置背景色
}

void GameLevel_1_1::Init()
{ 
	

	//地形

	// 云
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(180, 64);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(460, 48, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(484, 48, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(640, 64);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(815, 48, 0, 24);    
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(839, 48, 8, 16);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(855, 48, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1058, 64, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1082, 64, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1254, 48);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1441, 64, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1465, 64, 8, 16);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1481, 64, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1797, 48, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1821, 48, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(1977, 64);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(2140, 48, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(2164, 48, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCloud(2537, 64);

	// 草
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(354, 200, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(378, 200, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(564, 200, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(588, 200, 8, 16);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(604, 200, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(777, 200, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(801, 200, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(1159, 200, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(1183, 200, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(1580, 200, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(1604, 200, 8, 24);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(1943, 200, 0, 24);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(1967, 200, 8, 16);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBush(1983, 200, 8, 24);

	// 砖块
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(240, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(272, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(624, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(656, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(704, 160); G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(704, 104);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(736, 160); G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(736, 104);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(784, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(816, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1504, 144);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1536, 144);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1568, 80);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1584, 144);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1600, 80);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1648, 80);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1664, 80);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1680, 80);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1680, 80);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1728, 144);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1744, 144);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddBrick(1776, 144);

	// 问号砖块
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(256, 160, 1);; G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(256, 104);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(640, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(720, 160); G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(720, 104);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(800, 160);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(1520, 144, 1);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(1584, 80);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(1760, 144);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(1984, 144);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(2032, 144); G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(2032, 80, 1);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddLuckyBrick(2080, 144);

	// 硬砖块
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHardBrick(1248 - 16 * j, 152 + 16 * i);
		}
	}
    for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHardBrick(1312 + 16 * j, 152 + 16 * i);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHardBrick(2336 - 16 * j, 88 + 16 * i);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHardBrick(2352, 88 + 16 * i);
	}
	
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHardBrick(2480, 200);

	// 山
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHill(-5, 181);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHill(1417, 181);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHill(2104, 181);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddHill(2383, 181);

	// 小山
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddSmallHill(168, 197);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddSmallHill(970, 197);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddSmallHill(1766, 197);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddSmallHill(2652, 197);
	
	// 水管
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(322, 200);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeTop(320, 184);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(402, 200);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(402, 184);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeTop(400, 168);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(914, 200);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(914, 184);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeTop(912, 168);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(1074, 200);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(1074, 184);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(1074, 168);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeTop(1072, 152);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(1858, 200);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeTop(1856, 184);

	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeBody(2194, 200);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddPipeTop(2192, 184);

	// 城堡
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddCastle(2544, 136);

	// 旗子
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 184);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 168);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 152);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 136);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 120);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 104);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 88);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2487, 72);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2484, 65, 1);
	G_GameMgr.GameLevelMgr.GameObjectsMgr.AddFlag(2472, 72, 2);

	// 地面砖块
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 32; j++)
		{    
			G_GameMgr.GameLevelMgr.GameObjectsMgr.AddGroundBrick(0 + 16 * j, 216 + 16 * i);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 44; j++)
		{
			G_GameMgr.GameLevelMgr.GameObjectsMgr.AddGroundBrick(560 + 16 * j, 216 + 16 * i);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			G_GameMgr.GameLevelMgr.GameObjectsMgr.AddGroundBrick(1312 + 16 * j, 216 + 16 * i);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 65; j++)
		{
			G_GameMgr.GameLevelMgr.GameObjectsMgr.AddGroundBrick(1712 + 16 * j, 216 + 16 * i);
		}
	}



	// 敌怪

	EnemyMgr.Goombas.push_back({ 302, 200, 1, 0, 0, 2 });
	EnemyMgr.KoopaTroopas.push_back({ 640, 192, 1, 0, 0, 2 });
	EnemyMgr.Goombas.push_back({ 704, 200, 1, 0, 0, 2 });
	EnemyMgr.Goombas.push_back({ 768, 200, 1, 0, 0, 2 });
	EnemyMgr.Goombas.push_back({ 970, 200, 1, 0, 0, 2 });
	EnemyMgr.Goombas.push_back({ 1038, 200, 1, 0, 0, 2 });
	EnemyMgr.Goombas.push_back({ 1520, 120, 1, 0, 0, 2 });
	EnemyMgr.Goombas.push_back({ 1520, 120, 1, 0, 0, 2 });
	EnemyMgr.PiranhaPlants.push_back({ 1863, 160, 0, 1, 0, 2 });
	EnemyMgr.Goombas.push_back({ 1980, 200, 1, 0, 0, 2 });
	EnemyMgr.KoopaTroopas.push_back({ 2030, 192, 1, 0, 0, 2 });
	EnemyMgr.Goombas.push_back({ 2080, 200, 1, 0, 0, 2 });

}

void GameLevel_1_1::ShowInformations()
{
	setbkcolor(RGB(107, 140, 255)); // 设置背景色
	// 加载自定义字体并设置
	int fontResult = AddFontResourceEx(_T("resources/fonts/Fixedsys500c.ttf"), FR_PRIVATE, NULL);
	// 设置文本样式
	settextcolor(WHITE);
	settextstyle(12, 0, _T("FixedsysTTF"));
	//显示分数信息
	TCHAR ScoreText[50];
	_stprintf_s(ScoreText, _T("%06d"), P_PlayerMario.GetScore());//格式化为6位
	TCHAR CoinText[50];
	_stprintf_s(CoinText, _T("%02d"), P_PlayerMario.GetCoinCount());//格式化为2位
	int textX = (SCREEN_WIDTH) / 2;
	int textY = (SCREEN_HEIGHT / 2) - 50;
	outtextxy(20, 5, "SCORE");
	outtextxy(20, 13, ScoreText);
	outtextxy(87, 13, "*Coin");
	outtextxy(75, 13, CoinText);
	outtextxy(140, 5, "WORLD");
	outtextxy(140, 13, "1 - 1");
	outtextxy(210, 5, "TIME");

	TCHAR TimeText[50];
	_stprintf_s(TimeText, _T("%d"), P_PlayerMario.GetTimeCount());
	outtextxy(210, 13, TimeText);
}
