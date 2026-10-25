#pragma once
class GameCutscene
{
private:
	enum
	{
		E_GAME_CUTSCENE_OPENING,
		E_GAME_CUTSCENE_GAMEOVER
	};
	int CutScene;
public:
	GameCutscene();
	void SetCutScene(int InputCutscene);
	void Update();
	void Render();
	void RenderDeathScreen();
	void RenderGameOverScreen();
};

