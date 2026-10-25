#pragma once

class MusicMgr
{
private:
	float Timer;
	int Index;
	bool IfPlayBGM;
	char Command[120];
public:
	MusicMgr();
	void Play_BackgroundMusic_Level_1_1();
	void Play_Bump();
	void Play_BrickSmash();
	void Play_SmallJump();
	void Play_PowerUpAppear();
	void Play_PowerUp();
	void Play_Stomp();
	void Play_Death();
	void Play_Coin();
	void Play_FlagPole();
	void Stage_Clear();
	void InitBackgroundMusic();
	void CloseBackgroundMusic();
	void Update();
};

