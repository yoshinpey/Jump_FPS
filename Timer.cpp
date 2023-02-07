#include "Timer.h"

//コンストラクタ
Timer::Timer(GameObject* parent)
    :GameObject(parent, "Timer"), pText(nullptr)
{
}

//デストラクタ
Timer::~Timer()
{
}

//初期化
void Timer::Initialize()
{
    pText = new Text;
    pText->Initialize();
}

//更新
void Timer::Update()
{
}

//描画
void Timer::Draw()
{
    //pText->Draw(30, 30, "Hello");
}

//開放
void Timer::Release()
{
}