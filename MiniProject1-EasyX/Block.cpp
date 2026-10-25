#include "stdafx.h"
#include "Block.h"

extern Camera G_Camera;

Block::Block()
{
    XPosition = 0;
    YPosition = 0;
    CurrentXPosition = 0;
    CurrentYPosition = 0;
    BoxCollider.ColliderPosition_Left = 0;
    BoxCollider.ColliderPosition_Right = 0;
    BoxCollider.ColliderPosition_Top = 0;
    BoxCollider.ColliderPosition_Button = 0;
}

void Block::SetPosition(int InputXPosition, int InputYPosition)
{
    XPosition = InputXPosition;
    YPosition = InputYPosition;
    CurrentXPosition = InputXPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = InputYPosition - G_Camera.GetWorldYPosition();
}

void Block::SetCurrentPosition()
{
    CurrentXPosition = XPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = YPosition - G_Camera.GetWorldYPosition();
}

void Block::InitCollider()
{
    
}
