#pragma once
#include "Block.h"

class HardBrick : public Block
{
private:
	int Tag;
public:
	HardBrick();
	void DrawObject();
	virtual void InitCollider();
	int GetTag();
	bool CheckCollisionWithTag_0();
	void Update();
};

