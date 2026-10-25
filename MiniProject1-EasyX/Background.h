#pragma once
class Background
{
protected:
	int XPosition;
	int YPosition;
	int CurrentXPosition;
	int CurrentYPosition;
	IMAGE OrignImage;
public:
	Background();
	void SetPosition(int InputXPosition, int InputYPosition);
	void SetCurrentPosition();
};

