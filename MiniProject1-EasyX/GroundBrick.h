#pragma once
#include "Block.h"

class GroundBrick : public Block
{
private:
	int Tag;
public:
	GroundBrick();
	void DrawObject();
	virtual void InitCollider();
	int GetTag();
    void Update();
};

