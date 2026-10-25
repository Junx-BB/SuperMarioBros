#pragma once

class EnemyBase
{
protected:
	int XPosition;
	int YPosition;
	int CurrentXPosition;
	int CurrentYPosition;
	double XSpeed;//速度
	double YSpeed;
	int direction;//移动方向，0表示向左，1表示向右
	int Tag;//怪物标签
	int step_num;

	int frames;//帧数
	int f_speed;
	int index;
	int frameStart = GetTickCount64();
	int frameTime = 0;

	int TextPosition = 5;
	bool IsDrawText = false;
	int TextXPosition = 0;
	int TextYPosition = 0;

	IMAGE img_Enemy;
public:
	EnemyBase(int XPosition = 0, int YPosition = 0, double XSpeed = 0, double YSpeed = 0, int direction = 0, int Tag = 0, int step_num = 0, int frames = 2, int f_speed = 200, int index = 0);
	int GetXPositiion();
	int GetYPosition();
	int GetDirection();
	int GetTag();
	int GetStepNum();

	void SetCurrentPosition();

	bool JudgeCrash();
	void BeCrashed_KoopaTroopa();//与乌龟碰撞

	bool OnEnterColliderWithBlock_Left(Block& Block); // 判断是否与砖块在左侧重叠的函数
	bool OnEnterColliderWithBlock_Right(Block& Block); // 判断是否与砖块在右侧重叠的函数
	bool OnEnterColliderWithBlock_Top(Block& Block); // 判断是否与砖块在物体的上方重叠的函数
	bool OnEnterColliderWithBlock_Button(Block& Block); // 判断是否与砖块在物体的下方重叠的函数
	bool OnEnterColliderLeftWithTag_1(); // 判断是否与带有标签1的物体在左侧重叠的函数
	bool OnEnterColliderRightWithTag_1(); // 判断是否与带有标签1的物体在右侧重叠的函数
	bool OnEnterColliderTopWithTag_1(); // 判断是否与带有标签1的物体在物体的上方重叠的函数
	bool OnEnterColliderButtonWithTag_1(); // 判断是否与带有标签1的物体在物体的下方重叠的函数

	bool IsNearBlock_Top(Block& Block); // 判断是否贴着方块上侧的函数
	bool IsNearTopWithTag_1(); // 判断是否贴着标签为1的物体上侧的函数

	virtual void InitCollider() = 0;

	virtual void Move() = 0;
	virtual void ChangeDirection() = 0;
	virtual void Die() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	struct BoxCollider
	{
		int ColliderPosition_Left;
		int ColliderPosition_Right;
		int ColliderPosition_Top;
		int ColliderPosition_Button;
	};
	BoxCollider BoxCollider;

	int Spawn = false;
};