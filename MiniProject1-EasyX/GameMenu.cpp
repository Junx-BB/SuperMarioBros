#include "stdafx.h"
#include "GameMenu.h"

extern GameMgr G_GameMgr;


float ScreenHeight_Menu = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_Menu = ScreenHeight_Menu / 240; // 缩放倍率

GameMenu::GameMenu() : showStartPrompt(true), flashTimer(0)
{

}

void GameMenu::Update()
{

    bool StartKey = GetAsyncKeyState(VK_RETURN) < 0;
    if (StartKey)
    {
        G_GameMgr.SetGameScene(1);
        G_GameMgr.SetIsStartGame(true);
    }

    // 更新闪烁计时器
    flashTimer++;
    if (flashTimer >= flashInterval)
    {
        flashTimer = 0;
        showStartPrompt = !showStartPrompt; // 切换显示状态
    }
}

void GameMenu::Render()
{

    // 计算标题位置（居中）
    int hFont = AddFontResourceEx(_T("resources/fonts/Fixedsys500c.ttf"), FR_PRIVATE, NULL);

    settextstyle(12, 0, _T("FixedsysTTF"), 0, 0, 700, false, false, false);
    int titleX = SCREEN_WIDTH / 2;
    int titleY = SCREEN_HEIGHT / 3;

    // 绘制标题
    const TCHAR* text1 = _T("DESIGNED BY Legend JUNX LI");
    outtextxy(10, 180, text1);
    putimage(0, 50, &MenuImage[0]);


    // 绘制闪烁的"开始游戏"提示
    if (showStartPrompt)
    {
        // 设置文本样式
        settextcolor(BLACK);
        settextstyle(18, 0, _T("FixedsysTTF"));
        setbkmode(TRANSPARENT);

        // 绘制文本
        const TCHAR* text = _T("PRESS ENTER TO START");
        outtextxy(SCREEN_WIDTH / 10, SCREEN_HEIGHT - 90, text);


    }
}
void GameMenu::LoadMenuResource()
{
    IMAGE MenuSpriteSheet;

    loadimage(&MenuSpriteSheet, _T("resources/graphics/title_screen.png"), 257, 318);
    SetWorkingImage(&MenuSpriteSheet);
    getimage(&MenuImage[0], 1, 60, 176, 88);
    SetWorkingImage();
}
