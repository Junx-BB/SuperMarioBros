#pragma once
class GameMenu
{
private:
	IMAGE MenuImage[10];
	bool showStartPrompt; // ¿ØÖÆÉÁË¸×´Ì¬
	int flashTimer;      // ÉÁË¸¼ÆÊ±Æ÷
	const int flashInterval = 30; // ÉÁË¸¼ä¸ô£¨Ö¡Êı£©
public:
	GameMenu();
	void Update();
	void Render();
	void LoadMenuResource();
};

