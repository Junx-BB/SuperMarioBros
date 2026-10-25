#include "stdafx.h"

Camera G_Camera;
GameMgr G_GameMgr;
MusicMgr G_MusicMgr;
PlayerMario P_PlayerMario;
float G_Timer = 0;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

int main()
{
    int Scale = ScreenHeight/ 240; // 缩放倍率
    initgraph(SCREEN_WIDTH * Scale, SCREEN_HEIGHT * Scale);
    setaspectratio(Scale, Scale);

    // 加载资源
    P_PlayerMario.LoadResources();
    G_GameMgr.GameMenu.LoadMenuResource();
    
    DWORD LastTick = GetTickCount64();  // 记录上一帧时间（毫秒级）
    
    BeginBatchDraw(); // 开始批量绘图（开启双缓冲）
    
    while (true)
    {
        cleardevice(); // 清空设备（在内存中操作）

        G_GameMgr.Update();
        G_GameMgr.Render();

        line(0, 0, 0, 240);
        line(256, 0, 256, 240);
        
        FlushBatchDraw(); // 将内存中的图像一次性刷新到屏幕
        Sleep(16);  // 约60帧/秒
    }
}





// 关于Tag：
// 0为玩家
// 1为方块
// 2为伤害物体
// 3为道具