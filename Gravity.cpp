#include "Gravity.h"

//コンストラクタ
Gravity::Gravity(GameObject* parent)
    :GameObject(parent, "Gravity"), gravity_(-0.5)
{
}

//デストラクタ
Gravity::~Gravity()
{
}

//初期化
void Gravity::Initialize()
{
}

//更新
void Gravity::Update()
{
    //起動状態
    if (Active)
    {
        gravity_ += transform_.position_.y;//絶対値ゲーわ引数必要だろ寝よ。、、
        gravity_ -= 0.5;
    }
    
}

//描画
void Gravity::Draw()
{
}

//開放
void Gravity::Release()
{
}

//重力有効
void Gravity::GravityON()
{
    Active = true;
}

//重力無効
void Gravity::GravityOFF()
{
    Active = false;
}
