#include "stdafx.h"
#include "PlayerMario.h"
clock_t lastTime = 0;     // 上一帧时间

extern GameMgr G_GameMgr;
extern Camera G_Camera;
extern MusicMgr G_MusicMgr;

// 使用Windows API获取实际屏幕分辨率
float ScreenHeight_Mario = GetSystemMetrics(SM_CYFULLSCREEN);
int Scale_Mario = ScreenHeight_Mario / 240; // 缩放倍率

PlayerMario::PlayerMario()
{
    // 初始化马里奥
    mario.x = 40;
    mario.y = 200;
    mario.ScreenXPosition = mario.x - G_Camera.GetWorldXPosition();
    mario.ScreenYPosition = mario.y;
    mario.width = 40;
    mario.height = 60;
    mario.vx = 0;
    mario.vy = 0;
    mario.state = STAND;
    mario.onGround = false;
    mario.direction = 1;
    mario.frame = 0;
    mario.frameCount = 0;
    mario.keyPressed = false;   // 初始化按键状态
    mario.currentSpeed = 0;     // 初始化当前速度
    mario.lives = 3;
    mario.scores = 0;
    mario.isJumping = false;
    mario.jumpPressTime = 0;
    mario.canBigJump = true;   // 默认可以触发大跳
    mario.isBig = false;       // 默认是小马里奥
    mario.deathTimer = 0;
    mario.transTimer = 0;
    mario.flashTimer = 0;
    mario.flashInterval = 3;        // 设置闪烁间隔，可根据音乐节奏调整
    mario.transformFlashCount = 0;
    mario.isTransformingBig = false;
    mario.isTransformingSmall = false;
    Score = 0;
    Time = 180;
    Timer = 0;

    CanOverlap_Left = false;
    CanOverlap_Right = false;
    CanOverlap_Top = false;
    CanOverlap_Button = false;

    // 初始化碰撞箱
    InitCollider();

    resourcesLoaded = false;
    lastTime = clock();        // 初始化时间
}

void PlayerMario::ResetGame()
{
    // 复活处理 - 重置位置和摄像机
    mario.x = 40;  // 初始位置
    mario.y = 200;

    Time = 180;
    Timer = 0;
    mario.deathTimer = 0;

    // 关键修复：重置摄像机位置
    G_Camera.ResetPosition();  // 添加这个方法到摄像机类

    // 更新屏幕位置
    mario.ScreenXPosition = mario.x - G_Camera.GetWorldXPosition();
    mario.ScreenYPosition = mario.y;

    G_GameMgr.SetIsStartGame(false);

    FlagPullingComplete = false;
    //设置游戏状态
    G_GameMgr.SetGameScene(1);

    // 重置马里奥状态
    mario.state = STAND;
    mario.onGround = false;
    mario.vy = 0;
    mario.vx = 0;
    mario.isJumping = false;
    // 其他需要重置的状态...
    G_MusicMgr.InitBackgroundMusic();
    /*G_GameMgr.GameLevelMgr.GameObjectsMgr.ClearAllObjects();
    G_GameMgr.GameLevelMgr.GameObjectsMgr.ObjectReserve();
    G_GameMgr.GameLevelMgr.GameLevel_1_1.Init();*/
}
void PlayerMario::UpdateFlagSlide()
{

    if (EventsDispatcher_PlayerMario.GetIsFlagPulling())
    {
        mario.x = 2480;
        mario.vy = 0;
        mario.y += 2;
        FlagPullingComplete = true;
    }
    if (!EventsDispatcher_PlayerMario.GetIsFlagPulling() && FlagPullingComplete)
    {
        cout << mario.x << endl;
        if (mario.x >= 2580)
        {
            ResetGame();
            G_GameMgr.SetGameScene(0);

            mario.lives = 3;
        }
    }
    return;
}
bool PlayerMario::LoadResources()
{
    // 加载精灵图
    IMAGE spriteSheet;
    IMAGE spriteSheetTurn;
    loadimage(&spriteSheet, _T("resources/graphics/mario_bro.png"), 512 * Scale_Mario, 512 * Scale_Mario);
    if (spriteSheet.getwidth() <= 0) {
        outtextxy(10, 40, _T("精灵图加载失败!"));
        return false;
    }


    SetWorkingImage(&spriteSheet);

    // 普通马里奥 右- 站立、行走、跳跃
    getimage(&marioImages[0], 299 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 17 * Scale_Mario);   // 站立
    getimage(&marioImages[1], 396 * Scale_Mario, 59 * Scale_Mario, 15 * Scale_Mario, 17 * Scale_Mario);  // 行走1
    getimage(&marioImages[2], 411 * Scale_Mario, 59 * Scale_Mario, 15 * Scale_Mario, 17 * Scale_Mario);  // 行走2
    getimage(&marioImages[3], 426 * Scale_Mario, 59 * Scale_Mario, 18 * Scale_Mario, 17 * Scale_Mario);  // 行走3
    getimage(&marioImages[4], 266 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 17 * Scale_Mario);  // 跳跃

    // 大马里奥右 - 站立、行走、跳跃、蹲下
    getimage(&marioImages[5], 70 * Scale_Mario, 59 * Scale_Mario, 18 * Scale_Mario, 33 * Scale_Mario);   // 大站立
    getimage(&marioImages[6], 176 * Scale_Mario, 59 * Scale_Mario, 19 * Scale_Mario, 32 * Scale_Mario);  // 大行走1
    getimage(&marioImages[7], 195 * Scale_Mario, 59 * Scale_Mario, 16 * Scale_Mario, 32 * Scale_Mario);  // 大行走2
    getimage(&marioImages[8], 211 * Scale_Mario, 59 * Scale_Mario, 18 * Scale_Mario, 32 * Scale_Mario);  // 大行走3
    getimage(&marioImages[9], 0 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 32 * Scale_Mario);  // 大跳跃
    getimage(&marioImages[10], 34 * Scale_Mario, 59 * Scale_Mario, 19 * Scale_Mario, 24 * Scale_Mario); // 大蹲下

    // 普通马里奥 左- 站立、行走、跳跃
    getimage(&marioImages[11], 284 * Scale_Mario, 59 * Scale_Mario, 14 * Scale_Mario, 24 * Scale_Mario);//立
    getimage(&marioImages[12], 347 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 17 * Scale_Mario);//行走1
    getimage(&marioImages[13], 364 * Scale_Mario, 59 * Scale_Mario, 13 * Scale_Mario, 17 * Scale_Mario);//2
    getimage(&marioImages[14], 377 * Scale_Mario, 59 * Scale_Mario, 19 * Scale_Mario, 17 * Scale_Mario);//3
    getimage(&marioImages[15], 245 * Scale_Mario, 59 * Scale_Mario, 19 * Scale_Mario, 17 * Scale_Mario);//跳跃

    // 大马里奥 左- 站立、行走、跳跃、蹲下
    getimage(&marioImages[16], 53 * Scale_Mario, 59 * Scale_Mario, 18 * Scale_Mario, 33 * Scale_Mario);   // 大站立
    getimage(&marioImages[17], 125 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 32 * Scale_Mario);  // 大行走1
    getimage(&marioImages[18], 142 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 32 * Scale_Mario);  // 大行走2
    getimage(&marioImages[19], 158 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 32 * Scale_Mario);  // 大行走3
    getimage(&marioImages[20], 480 * Scale_Mario, 25 * Scale_Mario, 19 * Scale_Mario, 33 * Scale_Mario);  // 大跳跃
    getimage(&marioImages[21], 17 * Scale_Mario, 59 * Scale_Mario, 18 * Scale_Mario, 24 * Scale_Mario); // 大蹲下

    //小马里奥往左右刹车
    getimage(&marioImages[24], 316 * Scale_Mario, 59 * Scale_Mario, 15 * Scale_Mario, 17 * Scale_Mario);//往左
    getimage(&marioImages[25], 331 * Scale_Mario, 59 * Scale_Mario, 15 * Scale_Mario, 17 * Scale_Mario);//往右

    //大马里奥往左右刹车
    getimage(&marioImages[26], 88 * Scale_Mario, 59 * Scale_Mario, 19 * Scale_Mario, 31 * Scale_Mario);//往左
    getimage(&marioImages[27], 107 * Scale_Mario, 59 * Scale_Mario, 18 * Scale_Mario, 31 * Scale_Mario);//往右

    // 死亡动画
    getimage(&marioImages[22], 229 * Scale_Mario, 59 * Scale_Mario, 17 * Scale_Mario, 15 * Scale_Mario);  // 死亡（眼睛睁大）

    // 用于变大变小动画的中间图
    getimage(&marioImages[23], 463 * Scale_Mario, 25 * Scale_Mario, 18 * Scale_Mario, 25 * Scale_Mario);//往右
    SetWorkingImage(&spriteSheetTurn);
    getimage(&marioImages[28], 31 * Scale_Mario, 24 * Scale_Mario, 17 * Scale_Mario, 28 * Scale_Mario);//往左


    SetWorkingImage(); // 恢复默认工作图像
    resourcesLoaded = true;
    return true;
}

void PlayerMario::Update()
{
    if (!resourcesLoaded) return;

    // 计算时间增量
    clock_t currentTime = clock();
    double deltaTime = (currentTime - lastTime) / (double)CLOCKS_PER_SEC;
    lastTime = currentTime;

  // 死亡状态处理
    if (mario.state == DYING|| mario.y > SCREEN_HEIGHT) {
        mario.deathTimer += deltaTime;
        if (mario.deathTimer <= deltaTime) {  // 检测是否是死亡状态的第一帧
            mario.vy = JUMP_POWER * 0.6;
            G_MusicMgr.CloseBackgroundMusic();
            G_MusicMgr.Play_Death();
        }
        InitCollider();
        mario.vy += GRAVITY;
        mario.y += static_cast<int>(mario.vy);

        if (mario.deathTimer >= 5 || mario.y > SCREEN_HEIGHT) {
            mario.state = DEAD;
            mario.lives--;
            if (mario.lives <= 0) {
                // 游戏结束，重置、
                G_GameMgr.GameCutscene.SetCutScene(1);
                G_GameMgr.SetGameScene(2);
            }
            else {
                // 复活处理 - 重置位置和摄像机
                G_GameMgr.GameCutscene.SetCutScene(0);
                G_GameMgr.SetGameScene(2);
            }
        }
        return;  // 死亡状态不处理其他逻辑
    }

    //变大状态处理 
    if (mario.isTransformingBig && !mario.isBig)
    {

        mario.transTimer += deltaTime;
        mario.flashTimer++;

        // 根据计时器更新闪烁状态
        if (mario.flashTimer >= mario.flashInterval) {
            mario.flashTimer = 0;
            mario.transformFlashCount++;
        }
        if (mario.transTimer > 1)
        {

            mario.isBig = true;
            mario.isTransformingBig = false;
            mario.transTimer = 0;
            mario.transformFlashCount = 0;
            mario.vy = 0;  // 确保没有残留的下落速度
            if (mario.onGround) {
                mario.y -= 16;  // 小马里奥比大马里奥矮16px，需要调整
            }
        }
        mario.vx = 0;
        mario.MoveDirection = 0;
        mario.currentSpeed = 0;
        return;  // 不处理后续移动逻辑
    }
    //变小状态处理
    if (mario.isTransformingSmall && mario.isBig)
    {
        mario.transTimer += deltaTime;
        mario.flashTimer++;

        // 根据计时器更新闪烁状态
        if (mario.flashTimer >= mario.flashInterval) {
            mario.flashTimer = 0;
            mario.transformFlashCount++;
        }
        if (mario.transTimer > 1)
        {

            mario.isBig = false;
            mario.isTransformingSmall = false;
            mario.transTimer = 0;
            mario.transformFlashCount = 0;
            mario.vy = 0;  // 确保没有残留的下落速度
            // 变小后调整位置，确保脚在地面上
            if (mario.onGround) {
                mario.y += 16;  // 小马里奥比大马里奥矮16px，需要调整
            }
        }
        mario.vx = 0;
        mario.MoveDirection = 0;
        mario.currentSpeed = 0;
        return;  // 不处理后续移动逻辑
    }

    // 正常游戏逻辑
    mario.vx = 0;

    // 应用重力
    if (!mario.onGround)
    {
        mario.vy += GRAVITY;
    }

    // 先进行垂直移动
    if (IsNearTopWithTag_1() == false && OnEnterColliderLeftWithTag_1() == false && OnEnterColliderRightWithTag_1() == false  && OnEnterColliderTopWithTag_1() == false && OnEnterColliderButtonWithTag_1() == false)
    {
        mario.y += static_cast<int>(mario.vy);
    }
   
     // 长按加速逻辑
    bool leftKey = GetAsyncKeyState(VK_LEFT) < 0;
    bool rightKey = GetAsyncKeyState(VK_RIGHT) < 0;
    bool jumpKey = GetAsyncKeyState(VK_SPACE) < 0;
    bool downKey = GetAsyncKeyState(VK_DOWN) < 0;

    // 左右移动逻辑
    if (leftKey && mario.direction == 1)
    {
        // 从右向左切换，需要先减速
        mario.keyPressed = false;  // 视为松开按键，开始减速
        if (mario.onGround)
        {
            mario.state = mario.isBig ? BIG_BRAKE : BRAKE;
        }
        if (mario.currentSpeed <= 0.1) {  // 当速度接近零时，改变方向
            mario.direction = -1;
            mario.keyPressed = true;  // 重新开始加速
        }
    }
    else if (rightKey && mario.direction == -1) 
    {
        // 从左向右切换，需要先减速
        mario.keyPressed = false;
        if (mario.onGround)
        {
            mario.state = mario.isBig ? BIG_BRAKE : BRAKE;
        }
        if (mario.currentSpeed <= 0.1) {
            mario.direction = 1;
            mario.keyPressed = true;
        }
    }
    else {
        if (leftKey && !mario.isTransformingBig && !mario.isTransformingSmall) {
            if (IsNearRightWithTag_1() == false)
            {
                mario.keyPressed = true;
            }
            else
            {
                mario.keyPressed = false;
            }
            if (mario.onGround == true)
            {
                mario.direction = -1;
            }
            mario.MoveDirection = -1;
            mario.vx = mario.MoveDirection * INITIAL_SPEED;
            if (mario.onGround) mario.state = mario.isBig ? BIG_WALK : WALK;
        }
        else if ((rightKey || (FlagPullingComplete && !rightKey)) && !mario.isTransformingBig && !mario.isTransformingSmall) {
            if (IsNearLeftWithTag_1() == false)
            {
                mario.keyPressed = true;
            }
            else
            {
                mario.keyPressed = false;
            }
            if (mario.onGround == true)
            {
                mario.direction = 1;
            }
            mario.MoveDirection = 1;
            mario.vx = mario.MoveDirection * INITIAL_SPEED;
            if (mario.onGround) mario.state = mario.isBig ? BIG_WALK : WALK;
        }
        else if(EventsDispatcher_PlayerMario.GetIsFlagPulling() == false)
        {
            mario.keyPressed = false;
            if (mario.onGround && mario.currentSpeed == 0) {
                mario.state = mario.isBig ? BIG_STAND : STAND;
            }
        }
    }

    // 长按加速
    if (mario.keyPressed)
    {
        mario.currentSpeed += ACCELERATION * deltaTime;
    }
    else 
    {
        mario.currentSpeed -= DECELERATION * deltaTime;
    }

    if (mario.currentSpeed > MAX_SPEED) {
        mario.currentSpeed = MAX_SPEED;
    }
    if (mario.currentSpeed < 0) {
        mario.currentSpeed = 0;
    }

    // 设置实际速度
    mario.vx += mario.MoveDirection * mario.currentSpeed;

    // 水平移动
    if (mario.ScreenXPosition <= 0 && mario.vx < 0)
    {

    }
    else
    {
        if (mario.x > 2487) {
            mario.x += static_cast<int>(mario.vx * deltaTime * 100);
            mario.ScreenXPosition = mario.x - G_Camera.GetWorldXPosition();
        }
        else
        {
            mario.x += static_cast<int>(mario.vx * deltaTime * 100);
            if (mario.ScreenXPosition < 100 && mario.ScreenXPosition>0)
            {
                mario.ScreenXPosition = mario.x - G_Camera.GetWorldXPosition();
            }
            else if (mario.ScreenXPosition == 100 && mario.vx < 0)
            {
                mario.ScreenXPosition = mario.x - G_Camera.GetWorldXPosition();
            }
            else if (mario.ScreenXPosition == 0 && mario.vx > 0)
            {
                mario.ScreenXPosition = mario.x - G_Camera.GetWorldXPosition();
            }
            else if (mario.ScreenXPosition > 100)
            {
                mario.ScreenXPosition = 100;
            }
            else if (mario.ScreenXPosition < 0)
            {
                mario.ScreenXPosition = 0;
            }
        }
    }

    // 处理跳跃逻辑
    if (jumpKey) {
        if (mario.onGround && !mario.isJumping) {
            mario.isJumping = true;
            mario.onGround = false;
            mario.state = mario.isBig ? BIG_JUMP : JUMP;
            mario.vy = JUMP_POWER * 0.4f;  // 减小初始跳跃力度 (0.5 -> 0.4)
            mario.jumpPressTime = 0;
            mario.y--;
            mario.canBigJump = true;
            G_MusicMgr.Play_SmallJump();
        }
        else if (mario.isJumping && mario.canBigJump) {
            mario.jumpPressTime++;

            if (mario.jumpPressTime <= 7) {
                float pressRatio = (float)mario.jumpPressTime / 7;
                float easeFactor = 1.0f - (1.0f - pressRatio) * (1.0f - pressRatio);

                // 减小加速幅度 (0.3 -> 0.15) 并限制最大速度
                float minJumpFactor = 0.4f;
                float maxJumpFactor = 0.55f;  // 最大跳跃力度从0.8降到0.55

                mario.vy = JUMP_POWER * (minJumpFactor + (maxJumpFactor - minJumpFactor) * easeFactor);
            }
            else {
                mario.canBigJump = false;
            }
        }
    }
    else {
        mario.isJumping = false;
        mario.canBigJump = false;
    }

    // 跳起后状态变为下落
    if (mario.vy > 0 && mario.state == JUMP) {
        mario.state = FALL;
    }

    // 更新动画帧
    mario.frameCount++;
    if (mario.frameCount >= static_cast<int>(TARGET_FPS / 30)) {
        mario.frame = (mario.frame + 1) % 4;
        mario.frameCount = 0;
    }

    Timer += G_GameMgr.GetDeltaTime();

    if (Timer > 1)
    {
        Timer -= 1;
        Time--;

    }

    if (time == 0)
    {
        // 复活处理 - 重置位置和摄像机
        mario.lives--;
        G_GameMgr.GameCutscene.SetCutScene(0);
        G_GameMgr.SetGameScene(2);
        
    }

    UpdateFlagSlide();
    InitCollider();
    CanOverlap();
    IfCollitionNear();
    OnCollitionEnter();
    ChangeIsOnGroundState();

    CanOverlap_Left = false;
    CanOverlap_Right = false;
    CanOverlap_Top = false;
    CanOverlap_Button = false;

}

void PlayerMario::Render()
{
    if (!resourcesLoaded) {
        outtextxy(100, 100, _T("资源未加载，请检查图片路径"));
        return;
    }

    // 选择当前图片
    IMAGE* currentImage = &marioImages[0];
    int imageIndex = 0;
    int renderYOffset = 0;


    if (mario.direction == 1)
    {
        if (mario.state == DYING) {

            imageIndex = 22;

        }
        else if (mario.isTransformingBig)                  //变大动画
        {
            if (mario.transformFlashCount % 3 == 0) {


                imageIndex = 0;  // 小马里奥

            }
            else if (mario.transformFlashCount % 3 == 1)
            {
                renderYOffset = -8;
                imageIndex = 23;
            }
            else {
                renderYOffset = -16;
                imageIndex = 5;  // 大马里奥

            }
        }
        else if (mario.isTransformingSmall)
        {
            if (mario.transformFlashCount % 3 == 0) {


                imageIndex = 5;  //大马里奥

            }
            else if (mario.transformFlashCount % 3 == 1)
            {
                renderYOffset = 8;
                imageIndex = 23;
            }
            else {

                renderYOffset = 16;

                imageIndex = 0;  // 小马里奥

            }

        }
        else if (mario.state == BRAKE || mario.state == BIG_BRAKE)
        {
            imageIndex = mario.isBig ? 26 : 24;
        }
        else {
            // 根据大小和状态选择图片
            if (mario.isBig) {
                // 大马里奥
                if (mario.state == BIG_STAND) imageIndex = 5;
                else if (mario.state == BIG_WALK) imageIndex = 6 + (mario.frame % 3);
                else if (mario.state == BIG_JUMP || mario.state == BIG_FALL) imageIndex = 9;
                else if (mario.state == BIG_CROUCH) imageIndex = 10;
            }
            else {
                // 普通马里奥
                if (mario.state == STAND) imageIndex = 0;
                else if (mario.state == WALK) imageIndex = 1 + (mario.frame % 3);
                else if (mario.state == JUMP || mario.state == FALL) imageIndex = 4;
            }
        }
    }
    else if (mario.direction == -1)
    {

        if (mario.state == DYING) {
            // 死亡动画
            imageIndex = 22;

        }
        else if (mario.isTransformingBig)                  //变大动画
        {

            if (mario.transformFlashCount % 3 == 0) {



                imageIndex = 11;  // 小马里奥

            }
            else if (mario.transformFlashCount % 3 == 1)
            {
                renderYOffset = -8;
                imageIndex = 28;
            }
            else {
                renderYOffset = -16;
                imageIndex = 16;  // 大马里奥

            }
        }
        else if (mario.isTransformingSmall)
        {
            if (mario.transformFlashCount % 3 == 0) {


                imageIndex = 16;  // 大马里奥
            }
            else if (mario.transformFlashCount % 3 == 1)
            {
                renderYOffset = 8;
                imageIndex = 28;
            }
            else {

                renderYOffset = 16;
                imageIndex = 11;  // 小马里奥

            }

        }
        else if (mario.state == BRAKE || mario.state == BIG_BRAKE)
        {
            imageIndex = mario.isBig ? 27 : 25;
        }
        else {
            // 根据大小和状态选择图片
            if (mario.isBig) {
                // 大马里奥
                if (mario.state == BIG_STAND) imageIndex = 16;
                else if (mario.state == BIG_WALK) imageIndex = 17 + (mario.frame % 3);
                else if (mario.state == BIG_JUMP || mario.state == BIG_FALL) imageIndex = 20;
                else if (mario.state == BIG_CROUCH) imageIndex = 21;
            }
            else {
                // 普通马里奥
                if (mario.state == STAND) imageIndex = 11;
                else if (mario.state == WALK) imageIndex = 12 + (mario.frame % 3);
                else if (mario.state == JUMP || mario.state == FALL) imageIndex = 15;
            }
        }
    }

    currentImage = &marioImages[imageIndex];

    // 绘制当前图片
    if (mario.direction == 1) {
        DrawImg(mario.ScreenXPosition * Scale_Mario, (mario.y + renderYOffset) * Scale_Mario, currentImage);
    }

    else {
        DrawImg(mario.ScreenXPosition * Scale_Mario, (mario.y + renderYOffset) * Scale_Mario, currentImage);
    }

}

int PlayerMario::GetXPosition()
{
    return mario.x;
}

int PlayerMario::GetYPosition()
{
    return mario.y;
}

int PlayerMario::GetDirection()
{
    return mario.direction;
}

bool PlayerMario::GetIsBig()
{
    return mario.isBig;
}

void PlayerMario::SetIsBig(bool InputState)
{
    mario.isBig = InputState;
}

void PlayerMario::SetIsTransformingBig(bool InputState)
{
    mario.isTransformingBig = InputState;
}

int PlayerMario::GetLives()
{
    return mario.lives;
}

int PlayerMario::GetScore()
{
    return Score;
}

void PlayerMario::AddScore(int InputAddScore)
{
    Score += InputAddScore;
}

int PlayerMario::GetCoinCount()
{
    return CoinCount;
}

void  PlayerMario::AddCoinCount(int InputCoinCount)
{
    CoinCount += InputCoinCount;
}

int PlayerMario::GetTimeCount()
{
    return Time;
}

// 初始化碰撞箱
void PlayerMario::InitCollider()
{
    if (!mario.isBig)
    {
        BoxCollider.ColliderPosition_Left = mario.x - G_Camera.GetWorldXPosition();
        BoxCollider.ColliderPosition_Right = mario.x - G_Camera.GetWorldXPosition() + 13;
        BoxCollider.ColliderPosition_Top = mario.y;
        BoxCollider.ColliderPosition_Button = mario.y + 15;


    }
    else if (mario.isBig)
    {
        BoxCollider.ColliderPosition_Left = mario.x - G_Camera.GetWorldXPosition();
        BoxCollider.ColliderPosition_Right = mario.x - G_Camera.GetWorldXPosition() + 13;
        BoxCollider.ColliderPosition_Top = mario.y;
        BoxCollider.ColliderPosition_Button = mario.y + 31;

    }
}

void PlayerMario::CanOverlap()
{
    if (mario.vx > 0)
    {
        CanOverlap_Left = true;
    }
    if (mario.vx < 0)
    {
        CanOverlap_Right = true;
    }
    if (mario.vy > 0)
    {
        CanOverlap_Top = true;
    }
    if (mario.vy < 0)
    {
        CanOverlap_Button = true;
    }
}

// 当物体碰撞箱与其它物体碰撞箱重叠时触发的函数
void PlayerMario::OnCollitionEnter()
{
    // Tag_1
    while (OnEnterColliderLeftWithTag_1() == true)
    {
        mario.x--;
        mario.vx = 0;
        InitCollider();
    }
    while (OnEnterColliderRightWithTag_1() == true)
    {
        mario.x++;
        mario.vx = 0;
        InitCollider();
    }
    while (OnEnterColliderTopWithTag_1() == true)
    {
        mario.y--;
        InitCollider();
    }
    while (OnEnterColliderButtonWithTag_1() == true)
    {
        mario.y++;
        if (mario.vy < 0)
        {
            mario.vy = mario.vy * -1 / 2;
        }
        mario.canBigJump = false;
        InitCollider();
    }

    // Tag_2
    if (OnEnterColliderLeftWithTag_2() && !mario.isBig)
    {
        mario.state = DYING;
        InitCollider();
    }
    if (OnEnterColliderRightWithTag_2() && !mario.isBig)
    {
        mario.state = DYING;

        InitCollider();
    }
    if (OnEnterColliderTopWithTag_2() && !mario.isBig)
    {
        if (mario.vy >= 0)
        {
            mario.vy = JUMP_POWER * 0.3;
            G_MusicMgr.Play_Stomp();
            InitCollider();
        }
    }        
    if (OnEnterColliderLeftWithTag_2() && mario.isBig)
    {
        mario.isTransformingSmall = true;
        InitCollider();
    }
    if (OnEnterColliderRightWithTag_2() && mario.isBig)
    {
        mario.isTransformingSmall = true;
        InitCollider();
    }
    if (OnEnterColliderTopWithTag_2() && mario.isBig)
    {
        if (mario.vy >= 0)
        {
            mario.vy = JUMP_POWER * 0.3;
            G_MusicMgr.Play_Stomp();
            InitCollider();
        }
    }

    // Tag_3
    OnEnterColliderWithTag_3();// 判断是否与带有标签3的物体重叠的函数
}

// 当物体碰撞箱与其它物体碰撞箱贴着时触发的函数
void PlayerMario::IfCollitionNear()
{
    if (IsNearLeftWithTag_1() == true)
    {
        
    }
    if (IsNearRightWithTag_1() == true)
    {
        
    }
    if (IsNearTopWithTag_1() == true)
    {
        
    }
    if (IsNearButtonWithTag_1() == true)
    {
        
    }
}


// 判断是否与标签为1的物体重叠的函数

bool PlayerMario::OnEnterColliderLeftWithTag_1() // 判断是否与带有标签1的物体在左侧重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderRightWithTag_1() // 判断是否与带有标签1的物体在右侧重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderTopWithTag_1() // 判断是否与带有标签1的物体在物体的上方重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderButtonWithTag_1() // 判断是否与带有标签1的物体在物体的下方重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsOverlap = true;
            if (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i].BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right >= -7 || G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i].BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left <= 7)
            {

            }
            else
            {
                if (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i].SAnimation_Floating.IsFloating == false)
                {
                    G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i].SetIsEnterColliderWithPlayer_Top(true);
                }
            }
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsOverlap = true;
            if (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i].BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right >= -7 || G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i].BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left <= 7)
            {
                
            }
            else
            {
                if (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i].SAnimation_Floating.IsFloating == false)
                {
                    G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i].SetIsEnterColliderWithPlayer_Top(true);
                }
            }
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (OnEnterColliderWithBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}


// 判断是否与方块重叠的函数

bool PlayerMario::OnEnterColliderWithBlock_Left(Block& Block) // 判断是否与砖块在左侧重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Left > BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Right)
        {
            if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderWithBlock_Right(Block& Block) // 判断是否与砖块在右侧重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Left)
        {
            if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * -1 && Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderWithBlock_Top(Block& Block) // 判断是否与砖块在物体的上方重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) *(Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
        { 
            if (Block.BoxCollider.ColliderPosition_Left >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right <= BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderWithBlock_Button(Block& Block) // 判断是否与砖块在物体的下方重叠的函数
{
    bool IsOverlap = false;
    if ((Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Top && Block.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button && Block.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top)
        {
            if (Block.BoxCollider.ColliderPosition_Left >= BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right <= BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Left && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else
            {
                if (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top > Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top > (BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}

// 判断玩家是否贴着标签为1的物体的函数

bool PlayerMario::IsNearLeftWithTag_1() // 判断是否贴着标签为1的物体左侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (IsNearBlock_Left(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool PlayerMario::IsNearRightWithTag_1() // 判断是否贴着标签为1的物体右侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (IsNearBlock_Right(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool PlayerMario::IsNearTopWithTag_1() // 判断是否贴着标签为1的物体上侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true; 
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (IsNearBlock_Top(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool PlayerMario::IsNearButtonWithTag_1() // 判断是否贴着标签为1的物体下侧的函数
{
    bool IsNear = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGroundBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecLuckyBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecHardBricks[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeTops[i]))
        {
            IsNear = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys.size(); i++)
    {
        if (IsNearBlock_Button(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecPipeBodys[i]))
        {
            IsNear = true;
        }
    }
    return IsNear;
}

bool PlayerMario::IsNearBlock_Left(Block& Block) // 判断是否贴着方块左侧的函数
{
    bool IsNear = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right == 1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool PlayerMario::IsNearBlock_Right (Block& Block ) // 判断是否贴着方块右侧的函数
{
    bool IsNear = false;
    if ((Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Block.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left == -1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool PlayerMario::IsNearBlock_Top(Block& Block) // 判断是否贴着方块上侧的函数
{
    bool IsNear = false;
    if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Left)
    {
        if (Block.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button == 1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}
bool PlayerMario::IsNearBlock_Button(Block& Block) // 判断是否贴着方块下侧的函数
{
    bool IsNear = false;
    if (Block.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Right && Block.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Left)
    {
        if (Block.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top == -1)
        {
            IsNear = true;
        }
    }
    return IsNear;
}

// 判断是否与标签为2的物体重叠的函数
bool PlayerMario::OnEnterColliderLeftWithTag_2()// 判断是否与带有标签2的物体在左侧重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.Goombas.size(); i++)
    {
        if (OnEnterColliderWithEnemy_Left(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.Goombas[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas.size(); i++)
    {
        if (OnEnterColliderWithEnemy_Left(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas[i]))
        {
            if (G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas[i].GetStepNum() == 0 || G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas[i].GetStepNum() == 2)
            {
                IsOverlap = true;
            }
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.PiranhaPlants.size(); i++)
    {

        if (OnEnterColliderWithEnemy_Left(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.PiranhaPlants[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderRightWithTag_2()// 判断是否与带有标签2的物体在右侧重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.Goombas.size(); i++)
    {
        if (OnEnterColliderWithEnemy_Right(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.Goombas[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas.size(); i++)
    {
        if (OnEnterColliderWithEnemy_Right(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas[i]))
        {
            if (G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas[i].GetStepNum() == 0 || G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas[i].GetStepNum() == 2)
            {
                IsOverlap = true;
            }
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.PiranhaPlants.size(); i++)
    {

        if (OnEnterColliderWithEnemy_Right(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.PiranhaPlants[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderTopWithTag_2()// 判断是否与带有标签2的物体在上侧重叠的函数
{
    bool IsOverlap = false;
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.Goombas.size(); i++)
    {
        if (OnEnterColliderWithEnemy_Top(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.Goombas[i]))
        {
            IsOverlap = true;
        }

    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas.size(); i++)
    {

        if (OnEnterColliderWithEnemy_Top(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.KoopaTroopas[i]))
        {
            IsOverlap = true;
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.PiranhaPlants.size(); i++)
    {

        if (OnEnterColliderWithEnemy_Top(G_GameMgr.GameLevelMgr.GameLevel_1_1.EnemyMgr.PiranhaPlants[i]))
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}


// 判断是否与敌人重叠的函数
bool PlayerMario::OnEnterColliderWithEnemy_Left(EnemyBase& Enemy)// 判断是否与敌人在左侧重叠的函数
{
    bool IsOverlap = false;
    if ((Enemy.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Enemy.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Enemy.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Right && Enemy.BoxCollider.ColliderPosition_Left > BoxCollider.ColliderPosition_Left && Enemy.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Right)
        {
            if (Enemy.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Enemy.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else if (Enemy.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Enemy.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else
            {
                if (Enemy.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > Enemy.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button && Enemy.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right > (Enemy.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderWithEnemy_Right(EnemyBase& Enemy)// 判断是否与敌人在右侧重叠的函数
{
    bool IsOverlap = false;
    if ((Enemy.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Enemy.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
    {
        if (Enemy.BoxCollider.ColliderPosition_Right >= BoxCollider.ColliderPosition_Left && Enemy.BoxCollider.ColliderPosition_Right < BoxCollider.ColliderPosition_Right && Enemy.BoxCollider.ColliderPosition_Left <= BoxCollider.ColliderPosition_Left)
        {
            if (Enemy.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Top && Enemy.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else if (Enemy.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Enemy.BoxCollider.ColliderPosition_Button < BoxCollider.ColliderPosition_Button)
            {
                IsOverlap = true;
            }
            else
            {
                if (Enemy.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < (Enemy.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * -1 && Enemy.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left < Enemy.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}
bool PlayerMario::OnEnterColliderWithEnemy_Top(EnemyBase& Enemy)// 判断是否与敌人在上侧重叠的函数
{
    bool IsOverlap = false;
    if ((Enemy.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Enemy.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
    {
        if (Enemy.BoxCollider.ColliderPosition_Top <= BoxCollider.ColliderPosition_Button && Enemy.BoxCollider.ColliderPosition_Top > BoxCollider.ColliderPosition_Top && Enemy.BoxCollider.ColliderPosition_Button >= BoxCollider.ColliderPosition_Button)
        {
            if (Enemy.BoxCollider.ColliderPosition_Left >= BoxCollider.ColliderPosition_Left && Enemy.BoxCollider.ColliderPosition_Right <= BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else if (Enemy.BoxCollider.ColliderPosition_Left < BoxCollider.ColliderPosition_Left && Enemy.BoxCollider.ColliderPosition_Right > BoxCollider.ColliderPosition_Right)
            {
                IsOverlap = true;
            }
            else
            {
                if (Enemy.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > Enemy.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right && Enemy.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button > (Enemy.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) * -1)
                {
                    IsOverlap = true;
                }
            }
        }
    }
    return IsOverlap;
}

// 判断是否与标签为3的物体重叠的函数
void PlayerMario::OnEnterColliderWithTag_3()
{
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGrowMushrooms.size(); i++)
    {
        if (OnEnterColliderWithProp(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGrowMushrooms[i]))
        {
            G_GameMgr.GameLevelMgr.GameObjectsMgr.vecGrowMushrooms[i].SetIsEnterColliderWithPlayer(true);
        }
    }
    for (int i = 0; i < G_GameMgr.GameLevelMgr.GameObjectsMgr.vecFlags.size(); i++)
    {
        if (G_GameMgr.GameLevelMgr.GameObjectsMgr.vecFlags[i].GetPart() == 0)
        {
            if (OnEnterColliderWithProp(G_GameMgr.GameLevelMgr.GameObjectsMgr.vecFlags[i]))
            {
                EventsDispatcher_PlayerMario.SetIsFlagPulling(true);
            }
        }
    }
}

// 判断是否与道具重叠的函数
bool PlayerMario::OnEnterColliderWithProp(Prop& Prop)
{
    bool IsOverlap = false;
    if ((Prop.BoxCollider.ColliderPosition_Left - BoxCollider.ColliderPosition_Right) * (Prop.BoxCollider.ColliderPosition_Right - BoxCollider.ColliderPosition_Left) <= 0)
    {
        if ((Prop.BoxCollider.ColliderPosition_Top - BoxCollider.ColliderPosition_Button) * (Prop.BoxCollider.ColliderPosition_Button - BoxCollider.ColliderPosition_Top) <= 0)
        {
            IsOverlap = true;
        }
    }
    return IsOverlap;
}

void PlayerMario::ChangeIsOnGroundState()  // 判断玩家是否在地面上,修改OnGround的值
{
    if (IsNearTopWithTag_1() == true)
    {
        mario.onGround = true;
        mario.vy = 0;
    }
    /*else if (OnEnterColliderHorizaltalWithTag_1() == true || OnEnterColliderTopWithTag_1() == true || OnEnterColliderButtonWithTag_1() == true)
    {
        mario.onGround = true;
    }*/
    else if (IsNearTopWithTag_1() == false)
    {
        mario.onGround = false;
    }
}
