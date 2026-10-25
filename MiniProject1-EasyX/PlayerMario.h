#pragma once
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include "EventsDispatcher_PlayerMario.h"
#include "Block.h"
#include "EnemyBase.h"
#include "Prop.h"

#define GRAVITY 0.5       // 每帧重力加速度
#define JUMP_POWER -13     // 跳跃力度
#define INITIAL_SPEED 0.3 // 初速度
#define MAX_SPEED 1        // 最大移动速度（像素/秒）
#define ACCELERATION 2    // 加速度（像素/秒?）
#define DECELERATION 2     // 减速度（像素/秒?）
#define TARGET_FPS 60      // 目标帧率
#define FIXED_TIMESTEP 1.0/TARGET_FPS  // 固定时间步长（秒）

class PlayerMario
{
private:
    enum MarioState {
        STAND, WALK, JUMP, FALL, BRAKE,
        BIG_STAND, BIG_WALK, BIG_JUMP, BIG_FALL, BIG_CROUCH, BIG_BRAKE,  // 变大状态
        DYING, DEAD,                                             // 死亡状态
    };

    // 马里奥结构体
    struct Mario {
        int x, y;
        int ScreenXPosition, ScreenYPosition;
        int width, height;
        double vx, vy;          // 速度（浮点数，精确控制）
        MarioState state;
        bool onGround;
        int direction;          // 1:右 -1:左
        int MoveDirection;      // 1:右 -1:左
        int frame;              // 动画帧
        int frameCount;         // 帧计数器
        bool keyPressed;        // 按键是否被按下
        double currentSpeed;    // 当前速度（用于长按加速）
        bool isJumping;         // 是否正在跳跃
        int jumpPressTime;      // 跳跃按键按下的持续时间
        bool canBigJump;        // 是否可以触发大跳
        bool isBig;             // 是否变大
        double deathTimer;
        double transTimer;
        double flashTimer;           // 闪烁计时器
        double flashInterval;        // 闪烁间隔时间（秒）
        int transformFlashCount;
        bool isTransformingBig;
        bool isTransformingSmall;
        int lives;
        int scores;
    };

    Mario mario;
    IMAGE marioImages[50]; // 马里奥的不同状态图片
    IMAGE background;      // 背景图片
    bool resourcesLoaded;  // 资源是否已加载
    bool CanOverlap_Left;
    bool CanOverlap_Right;
    bool CanOverlap_Top;
    bool CanOverlap_Button;
    int Score; // 角色获得的分数
    int CoinCount;
    int Time;
    float Timer;
    int m_FlagSlideX = 0; // 滑旗时的固定X位置
    bool FlagPullingComplete = false;

public:
    PlayerMario();
    void ResetGame();
    void UpdateFlagSlide();
    bool LoadResources();  // 加载资源函数
    void Update();
    void Render();
    int GetXPosition();
    int GetYPosition();
    int GetDirection();
    bool GetIsBig();
    void SetIsBig(bool InputState);
    void SetIsTransformingBig(bool InputState);
    int GetLives();
    int GetScore();
    void AddScore(int InputAddScore); // 将分数的值设置为原来的分数加上参数值
    int GetCoinCount();
    void AddCoinCount(int InputCoinCount);
    int GetTimeCount();
    void InitCollider(); // 初始化碰撞箱的函数
    void CanOverlap(); // 判断是否能发生某方向的重叠的函数
    void OnCollitionEnter(); // 当物体碰撞箱子与其它物体碰撞箱重叠时触发的函数
    void IfCollitionNear();  // 当物体碰撞箱与其它物体碰撞箱贴着时触发的函数
    bool OnEnterColliderLeftWithTag_1(); // 判断是否与带有标签1的物体在左侧重叠的函数
    bool OnEnterColliderRightWithTag_1(); // 判断是否与带有标签1的物体在右侧重叠的函数
    bool OnEnterColliderTopWithTag_1(); // 判断是否与带有标签1的物体在物体的上方重叠的函数
    bool OnEnterColliderButtonWithTag_1(); // 判断是否与带有标签1的物体在物体的下方重叠的函数
    bool OnEnterColliderWithBlock_Left(Block& Block); // 判断是否与砖块在左侧重叠的函数
    bool OnEnterColliderWithBlock_Right(Block& Block); // 判断是否与砖块在右侧重叠的函数
    bool OnEnterColliderWithBlock_Top(Block& Block); // 判断是否与砖块在物体的上方重叠的函数
    bool OnEnterColliderWithBlock_Button(Block& Block); // 判断是否与砖块在物体的下方重叠的函数
    bool IsNearLeftWithTag_1(); // 判断是否贴着标签为1的物体左侧的函数
    bool IsNearRightWithTag_1(); // 判断是否贴着标签为1的物体上侧的函数
    bool IsNearTopWithTag_1(); // 判断是否贴着标签为1的物体下侧的函数
    bool IsNearButtonWithTag_1(); // 判断是否贴着标签为1的物体右侧的函数
    bool IsNearBlock_Left(Block& Block); // 判断是否贴着方块左侧的函数
    bool IsNearBlock_Right(Block& Block); // 判断是否贴着方块右侧的函数
    bool IsNearBlock_Top(Block& Block); // 判断是否贴着方块上侧的函数
    bool IsNearBlock_Button(Block& Block); // 判断是否贴着方块下侧的函数
    bool OnEnterColliderLeftWithTag_2(); // 判断是否与带有标签2的物体在左侧重叠的函数
    bool OnEnterColliderRightWithTag_2(); // 判断是否与带有标签2的物体在右侧重叠的函数
    bool OnEnterColliderTopWithTag_2(); // 判断是否与带有标签2的物体在物体的上方重叠的函数
    bool OnEnterColliderWithEnemy_Left(EnemyBase& Enemy);// 判断是否与敌人在左侧重叠的函数
    bool OnEnterColliderWithEnemy_Right(EnemyBase& Enemy);// 判断是否与敌人在右侧重叠的函数
    bool OnEnterColliderWithEnemy_Top(EnemyBase& Enemy);//判断是否与敌人在上侧重叠的函数
    void OnEnterColliderWithTag_3();// 判断是否与带有标签3的物体重叠的函数
    bool OnEnterColliderWithProp(Prop& Prop);//判断是否与道具在重叠的函数
    void ChangeIsOnGroundState(); // 判断玩家是否在地面上，修改OnGround的值
    EventsDispatcher_PlayerMario EventsDispatcher_PlayerMario;

    struct BoxCollider
    {
        int ColliderPosition_Left;
        int ColliderPosition_Right;
        int ColliderPosition_Top;
        int ColliderPosition_Button;
    };
    BoxCollider BoxCollider;
};