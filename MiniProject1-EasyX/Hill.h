#pragma once
#include "Background.h"

class Hill : public Background
{
private:
	IMAGE OrignImage;
public:
	Hill();
	void DrawObject();
	void Update();
};

