#include "Timer.h"
#include "Engine/Input.h"

static const int FPS = 60;

//コンストラクタ
Timer::Timer(GameObject* parent)
    :GameObject(parent, "Timer"), pNum(nullptr),
    Frame(0), Active(false), drawX(0), drawY(0)
{
}

//デストラクタ
Timer::~Timer()
{
}

//初期化
void Timer::Initialize()
{
    pNum = new Text;
    pNum->Initialize();
}

//更新
void Timer::Update()
{
    if (Active) 
    {
        if (Frame > 0) 
        {
            Frame--;
        }
    }
}

//描画
void Timer::Draw()
{
    pNum->SetScale(1.0f);
    pNum->Draw(drawX, drawY, "Time");
    if (Frame % FPS < 10)
        pNum->SetScale((Frame % FPS) * 0.2f + 1.0f);
    else
        pNum->SetScale(1.0f);
    int sec = Frame / FPS;
    pNum->Draw(drawX + 100, drawY, sec);
}

//開放
void Timer::Release()
{
}

//タイマー設定
void Timer::SetLimit(float seconds)
{
    Frame = (int)(seconds * FPS);
}

//タイマー開始
void Timer::TimeStart()
{
    Active = true;
}

//タイマー終了
void Timer::TimeStop()
{
    Active = false;
}

//タイマー処理終了
bool Timer::IsFinished()
{
    return (Frame == 0);
}
