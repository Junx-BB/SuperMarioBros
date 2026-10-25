#pragma once
#include "Block.h"

class PipeTop : public Block
{
private:
	int Tag;
public:
	PipeTop();
	void DrawObject();
	virtual void InitCollider();
	int GetTag();
	bool GetIsEnterColliderWithPlayer_Top();
	void SetIsEnterColliderWithPlayer_Top(bool State = true);
	void Update();
};

