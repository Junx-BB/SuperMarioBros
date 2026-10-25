#include "stdafx.h"
#include "Background.h"

extern Camera G_Camera;

Background::Background()
{
    XPosition = 0;
    YPosition = 0;
    CurrentXPosition = 0;
    CurrentYPosition = 0;
}

void Background::SetPosition(int InputXPosition, int InputYPosition)
{
    XPosition = InputXPosition;
    YPosition = InputYPosition;
    CurrentXPosition = InputXPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = InputYPosition - G_Camera.GetWorldYPosition();
}

void Background::SetCurrentPosition()
{
    CurrentXPosition = XPosition - G_Camera.GetWorldXPosition();
    CurrentYPosition = YPosition - G_Camera.GetWorldYPosition();
}
