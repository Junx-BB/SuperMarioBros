#pragma once
#include "Block.h"

class PipeBody : public Block
{
private:
	int Tag;
public:
	PipeBody();
	void DrawObject();
	virtual void InitCollider();
	int GetTag();
	void Update();
};

