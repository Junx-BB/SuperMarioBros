#include "stdafx.h"
#include "Text.h"

extern Camera G_Camera;
extern GameMgr G_GameMgr;

Text::Text()
{
	Type = -1;
	XPosition = 0;
	YPosition = 0;
	CurrentYPosition = 0;
}

void Text::Init(int InputXPosition, int InputYposition, string InputText)
{
	XPosition = InputXPosition;
	YPosition = InputYposition;
	CurrentYPosition = InputYposition;
	Content = InputText;
}

void Text::Update()
{
	if (Type = -1)
	{
		CurrentYPosition--;
		if (YPosition - CurrentYPosition >= 20)
		{
			for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
			{
				if (this == &G_GameMgr.vecTexts[i])
				{
					G_GameMgr.vecTexts.erase(G_GameMgr.vecTexts.begin() + i);
				}
			}
		}
	}
}

void Text::Render()
{
	if (Type = -1)
	{
		settextstyle(8, 0, _T("FixedsysTTF"));
		setbkmode(TRANSPARENT);
		outtextxy(XPosition - G_Camera.GetWorldXPosition(), CurrentYPosition, Content.c_str());
	}
}