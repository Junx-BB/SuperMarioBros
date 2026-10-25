#pragma once

class Camera
{
private:
	int WorldXPosition; // 在世界中的X轴坐标
	int WorldYPosition; // 在世界中的Y轴坐标
public:
	Camera();
	void Update();
	int GetWorldXPosition();
	int GetWorldYPosition();
	void ResetPosition();
};

