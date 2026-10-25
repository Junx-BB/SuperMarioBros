#pragma once

class Block
{
protected:
	int XPosition;
	int YPosition;
	int CurrentXPosition;
	int CurrentYPosition;
	IMAGE OrignImage;
public:
	Block();
	void SetPosition(int InputXPosition, int InputYPosition);
	void SetCurrentPosition();
	virtual void InitCollider();

	struct BoxCollider
	{
		int ColliderPosition_Left;
		int ColliderPosition_Right;
		int ColliderPosition_Top;
		int ColliderPosition_Button;
	};
	BoxCollider BoxCollider;
};

