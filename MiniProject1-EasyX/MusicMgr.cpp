#include "stdafx.h"
#include "MusicMgr.h"

extern GameMgr G_GameMgr;

MusicMgr::MusicMgr()
{
    Timer = 0;
    Index = 0;
    IfPlayBGM = true;
    Command[100] = { 0 };
}

void MusicMgr::Play_BackgroundMusic_Level_1_1()
{
    mciSendString(TEXT("open \"resources\\music\\main_theme.wav\" alias BGM"), NULL, 0, NULL); // 打开音乐
    mciSendString(TEXT("play BGM"), NULL, 0, NULL); // 播放音乐
}

void MusicMgr::Play_Bump()
{   
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\sound\\bump.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_BrickSmash()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\sound\\brick_smash.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_SmallJump()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\sound\\small_jump.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_PowerUpAppear()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\sound\\powerup_appear.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_PowerUp()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\sound\\powerup.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_Stomp()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\sound\\stomp.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_Death()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\music\\death.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_Coin()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\sound\\coin.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Play_FlagPole()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\music\\flagpole.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::Stage_Clear()
{
    // 生成带索引的打开命令
    sprintf_s(Command, sizeof(Command),
        "open \"resources\\music\\stage_clear.wav\" alias Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    // 生成匹配的播放命令
    sprintf_s(Command, sizeof(Command), "play Death%d", Index);
    mciSendStringA(Command, NULL, 0, NULL);

    //mciSendString(TEXT("close Death"), NULL, 0, NULL); // 播放完成后关闭

    Command[100] = { 0 };
    Index++;
}

void MusicMgr::InitBackgroundMusic()
{
    IfPlayBGM = true;
    Timer = 0;
    mciSendString(TEXT("close BGM"), NULL, 0, NULL);
}

void MusicMgr::CloseBackgroundMusic()
{
    IfPlayBGM = false;
    Timer = 0;
    mciSendString(TEXT("close BGM"), NULL, 0, NULL);
}

void MusicMgr::Update()
{
    if (IfPlayBGM == true)
    {
        Timer = 0;
        mciSendString(TEXT("open \"resources\\music\\main_theme.wav\" alias BGM"), NULL, 0, NULL); // 打开音乐
        mciSendString(TEXT("play BGM"), NULL, 0, NULL); // 播放音乐
        IfPlayBGM = false;
    }

    Timer += (float)G_GameMgr.GetDeltaTime();
    if (Timer >= 77)
    {
        mciSendString(TEXT("close BGM"), NULL, 0, NULL);
        IfPlayBGM = true;
    }
}