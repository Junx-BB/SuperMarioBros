#pragma once
#include "Prop.h"

class Flag : public Prop
{
private:
	int Part; // 旗的部分，0为旗杆，1为旗头，2为旗帜
	IMAGE OrignImage1;
	IMAGE OrignImage2;
public:
	Flag();
	void DrawObject();
	virtual void InitCollider();
	int GetPart();
	void SetPart(int InputPart);
	void OnCollitionEnter(); // 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
	void OnCollitionEnterWithPlayer(); // 与玩家重叠时调用的函数
	void Animator(); // 动画器
	void Animation_Descend(); // 旗子下降动画
	void Update();

	struct SAnimation_Descend // 旗子下降动画的结构体
	{
		int IsPlayingDescendMusic = 0;
		bool MusicStageClearHavePlayed = false;
	};
	SAnimation_Descend SAnimation_Descend;
};

