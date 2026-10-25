#pragma once
#include "Block.h"

class EmptyLuckyBrick : public Block
{
private:
	int Tag;
public:
	EmptyLuckyBrick();
	void DrawObject();
	virtual void InitCollider();
	int GetTag();
	void Update();
};


