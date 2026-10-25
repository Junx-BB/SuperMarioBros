#include "stdafx.h"

extern Camera G_Camera;
extern MusicMgr G_MusicMgr;

GameMgr::GameMgr()
{
	GameScene = E_GAME_MENU;
	ViewportX = 0;
	ViewportY = 0;
	DeltaTime = 0;
    IsStartGame = false;
}

GameMgr::~GameMgr()
{
	
}

void GameMgr::Update()
{
	if (GameScene == E_GAME_MENU)
	{
        GameMenu.Update();
        if (IsStartGame == true)
        {
            GameLevelMgr.Update();
        }
	}
	else if (GameScene == E_GAME_LEVEL)
	{
        G_MusicMgr.Update();
		GameLevelMgr.Update();
	}
	else if (GameScene == E_GAME_CUTSCENE)
	{
		GameCutscene.Update();
	}

    TextUpdate();
    G_Camera.Update();

	// 2. 计算帧间时间
	auto currentTime = high_resolution_clock::now();
	DeltaTime = duration_cast<duration<float>>(currentTime - lastFrameTime).count();
	lastFrameTime = currentTime;
}

void GameMgr::Render()
{
	if (GameScene == E_GAME_MENU)
	{
        GameLevelMgr.Render();
		GameMenu.Render();
	}
	else if (GameScene == E_GAME_LEVEL)
	{
		GameLevelMgr.Render();
	}
	else if (GameScene == E_GAME_CUTSCENE)
	{
		GameCutscene.Render();
	}

    TextRender();
}

float GameMgr::GetDeltaTime()
{
	return DeltaTime;
}

void GameMgr::SetGameScene(int InputGameScene)
{
    GameScene = InputGameScene;
}

void GameMgr::AddFloatingText(int InputXPosition, int InputYposition, string InputText)
{
    Text Text;
    Text.Init(InputXPosition, InputYposition, InputText);
    vecTexts.push_back(Text);
}

void GameMgr::TextUpdate()
{
    for (int i = 0; i < vecTexts.size(); i++)
    {
        vecTexts[i].Update();
    }
}

void GameMgr::TextRender()
{
    for (int i = 0; i < vecTexts.size(); i++)
    {
        vecTexts[i].Render();
    }
}

void GameMgr::SetIsStartGame(bool InputState)
{
    IsStartGame = InputState;
}

void DrawImg(int x, int y, int dstW, int dstH, IMAGE* src, int srcX, int srcY)
{
    // 变量初始化	
    DWORD* pwin = GetImageBuffer();
    // 	//窗口缓冲区指针	
    DWORD* psrc = GetImageBuffer(src);
    //图片缓冲区指针
    int win_w = getwidth();
    //窗口宽高	
    int win_h = getheight();
    int src_w = src->getwidth();
    //图片宽高
    int src_h = src->getheight();
    // 计算贴图的实际长宽
    int real_w = (x + dstW > win_w) ? win_w - x : dstW;
    // 处理超出右边界
    int real_h = (y + dstH > win_h) ? win_h - y : dstH;
    // 处理超出下边界	
    if (x < 0) {
        psrc += -x;
        real_w -= -x;	x = 0;
    }
    // 处理超出左边界
    if (y < 0)
    {
        psrc += (dstW * -y);
        real_h -= -y;
        y = 0;
    }
    // 处理超出上边界	
    //printf("realw,h(%d,%d)\n", real_w, real_h);	
    // 修正贴图起始位置
    pwin += (win_w * y + x);
    // 实现透明贴图
    for (int iy = 0; iy < real_h; iy++)
    {
        for (int ix = 0; ix < real_w; ix++)
        {
            byte a = (byte)(psrc[ix + srcX + srcY * src_w] >> 24);//计算透明通道的值[0,256) 0为完全透明 255为完全不透明	
            if (a > 100)
            {
                pwin[ix] = psrc[ix + srcX + srcY * src_w];
            }
        }
        //换到下一行		
        pwin += win_w;
        psrc += src_w;
    }
}

void DrawImg(int x, int y, IMAGE* src)
{
    // 变量初始化
    DWORD* pwin = GetImageBuffer();
    //窗口缓冲区指针	
    DWORD* psrc = GetImageBuffer(src);
    //图片缓冲区指针	
    int win_w = getwidth();
    //窗口宽高
    int win_h = getheight();
    int src_w = src->getwidth();
    //图片宽高	
    int src_h = src->getheight();
    // 计算贴图的实际长宽	
    int real_w = (x + src_w > win_w) ? win_w - x : src_w;
    // 处理超出右边界	
    int real_h = (y + src_h > win_h) ? win_h - y : src_h;
    // 处理超出下边界	
    if (x < 0)
    {
        psrc += -x;
        real_w -= -x;	x = 0;
    }	// 处理超出左边界	
    if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	// 处理超出上边界	
    // 修正贴图起始位置	
    pwin += (win_w * y + x);
    // 实现透明贴图	
    for (int iy = 0; iy < real_h; iy++)
    {
        for (int ix = 0; ix < real_w; ix++)
        {
            byte a = (byte)(psrc[ix] >> 24);//计算透明通道的值[0,256) 0为完全透明 255为完全不透明		
            if (a > 100)
            {
                pwin[ix] = psrc[ix];
            }
        }
        //换到下一行	
        pwin += win_w;
        psrc += src_w;
    }
}
