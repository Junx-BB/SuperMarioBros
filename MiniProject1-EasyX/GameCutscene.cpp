#include "stdafx.h"
#include "GameCutscene.h"

extern PlayerMario P_PlayerMario;
extern GameMgr G_GameMgr;

float ScreenHeight_Cutscene = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_Cutscene = ScreenHeight_Cutscene / 240; // 缩放倍率
const double DEATH_SCREEN_DURATION = 2.0;  // 死亡页面显示时间（秒）

GameCutscene::GameCutscene()
{
    CutScene = -1;
}

void GameCutscene::SetCutScene(int InputCutscene)
{
    CutScene = InputCutscene;
}

void GameCutscene::Update()
{
    if (CutScene == E_GAME_CUTSCENE_OPENING) {
        // 死亡页面计时器
        static double deathScreenTimer = 0.0;
        deathScreenTimer += G_GameMgr.GetDeltaTime();

        // 检查是否达到显示时间
        if (deathScreenTimer >= DEATH_SCREEN_DURATION) {
            deathScreenTimer = 0.0;

            // 重置游戏
            P_PlayerMario.ResetGame();

            // 切换回游戏关卡
            G_GameMgr.SetGameScene(1);
        }
    }
}

void GameCutscene::Render()
{

    if (CutScene == E_GAME_CUTSCENE_OPENING)
    {
        RenderDeathScreen();
    }
    else if (CutScene == E_GAME_CUTSCENE_GAMEOVER) {
        // 渲染死亡页面（覆盖全屏）
        RenderGameOverScreen();
    }
}
void GameCutscene::RenderDeathScreen() {

    setfillcolor(BLACK);
    solidrectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // 加载自定义字体并设置
    int fontResult = AddFontResourceEx(_T("resources/fonts/Fixedsys500c.ttf"), FR_PRIVATE, NULL);
    // 设置文本样式
    settextcolor(WHITE);
    settextstyle(18, 0, _T("FixedsysTTF"));
    setbkmode(TRANSPARENT);

    // 加载并绘制马里奥图像（建议移到初始化函数中）
    static IMAGE JUNX;

    IMAGE spriteSheet;
    // 检查图像加载结果
    loadimage(&spriteSheet, _T("resources/graphics/mario_bro.png"), 512 * Scale_Cutscene, 512 * Scale_Cutscene);
    SetWorkingImage(&spriteSheet);
    getimage(&JUNX, 299 * Scale_Cutscene, 59 * Scale_Cutscene,
        17 * Scale_Cutscene, 17 * Scale_Cutscene);


    SetWorkingImage();


    // 显示生命值信息
    TCHAR livesText[50];
    _stprintf_s(livesText, _T("       X      %d"), P_PlayerMario.GetLives());

    //显示分数信息
    TCHAR ScoreText[50];
    _stprintf_s(ScoreText, _T("%05d"), P_PlayerMario.GetScore()); // 格式化为6位，不足前面补0


    TCHAR CoinText[50];
    _stprintf_s(CoinText, _T("%02d"), P_PlayerMario.GetCoinCount());//格式化为2位

    // 计算文本位置使其居中
    int textX = (SCREEN_WIDTH - textwidth(livesText)) / 2;
    int textY = (SCREEN_HEIGHT / 2) - 50;



    // 绘制马里奥图像（如果加载成功）

    int imgX = textX - 10; // 图像在文本左侧
    int imgY = textY - 1;
    DrawImg(imgX * Scale_Cutscene, imgY * Scale_Cutscene, &JUNX);


    // 绘制文本
    outtextxy(textX, textY, livesText);


    settextstyle(12, 0, _T("FixedsysTTF"));
    //分数，关卡，金币
    outtextxy(20, 5, "SCORE");
    outtextxy(20, 13, ScoreText);
    outtextxy(87, 13, "*Coin");
    outtextxy(75, 13, CoinText);
    outtextxy(140, 5, "WORLD");
    outtextxy(140, 13, "1 - 1");
    outtextxy(210, 5, "TIME");

}

void GameCutscene::RenderGameOverScreen()
{
    setfillcolor(BLACK);
    solidrectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // 加载自定义字体并设置
    int fontResult = AddFontResourceEx(_T("resources/fonts/Fixedsys500c.ttf"), FR_PRIVATE, NULL);
    // 设置文本样式
    settextcolor(WHITE);
    settextstyle(18, 0, _T("FixedsysTTF"));
    int textX = (SCREEN_WIDTH) / 2 - 50;
    int textY = (SCREEN_HEIGHT / 2) - 30;
    outtextxy(textX, textY, "GAME   OVER");

}