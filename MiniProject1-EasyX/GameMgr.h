#pragma once
#include <chrono>
#include "GameMenu.h"
#include "GameLevelMgr.h"
#include "GameCutscene.h"
#include "Text.h"
#include "Camera.h"

#define SCREEN_WIDTH 256 // 视口的宽度
#define SCREEN_HEIGHT 240 // 视口的高度
#define LEVEL_WIDTH 256 // 关卡的宽度
#define LEVEL_HEIGHT 240 // 关卡的长度

using namespace std::chrono;

class GameMgr
{
private:
	enum
	{
		E_GAME_MENU,
		E_GAME_LEVEL,
		E_GAME_CUTSCENE
	};
	int GameScene;
	int ViewportX; // 视口X轴位置
	int ViewportY; // 视口Y轴位置
	high_resolution_clock::time_point lastFrameTime = high_resolution_clock::now(); // 定义计时变量
	float DeltaTime; // 帧间时间
	bool IsStartGame;
public:
	GameMgr();
	~GameMgr();
	void Init();
	float GetDeltaTime();
	void SetGameScene(int InputGameScene);
	void AddFloatingText(int InputXPosition, int InputYposition, string InputText);
	void TextUpdate();
	void TextRender();
	void SetIsStartGame(bool InputState);
	void Update();
	void Render();

	vector<Text> vecTexts;

	GameMenu GameMenu;
	GameLevelMgr GameLevelMgr;
	GameCutscene GameCutscene;
};

void DrawImg(int x, int y, int dstW, int dstH, IMAGE* src, int srcX, int srcY);
void DrawImg(int x, int y, IMAGE* src);