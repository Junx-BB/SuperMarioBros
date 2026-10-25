#include "stdafx.h"
#include "Camera.h"

extern GameMgr G_GameMgr;
extern PlayerMario P_PlayerMario;

Camera::Camera()
{
	WorldXPosition = 0;
	WorldYPosition = 0;
}

void Camera::Update()
{
	if (P_PlayerMario.GetXPosition()- WorldXPosition>100 && WorldXPosition < 2448)
	{
		WorldXPosition = P_PlayerMario.GetXPosition() - 100;
	}
}

int Camera::GetWorldXPosition()
{
	return WorldXPosition;
}

int Camera::GetWorldYPosition()
{
	return WorldYPosition;
}

void Camera::ResetPosition()
{
	WorldXPosition = 0;  // ³õÊ¼Î»ÖÃ
}
