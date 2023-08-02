#include "Engine/Model.h"
#include "Enemy_Fly.h"


//コンストラクタ
Enemy_Fly::Enemy_Fly(GameObject* parent)
    :GameObject(parent, "Enemy_Fly"), hModel_(-1)
{
}

//デストラクタ
Enemy_Fly::~Enemy_Fly()
{
}

//初期化
void Enemy_Fly::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Character/Mob_Robot.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = 1;
    transform_.position_.z = 10;
    transform_.rotate_.y = 180;

    //アニメーション
    Model::SetAnimFrame(hModel_, 0, 120, 1.00);

}

//更新
void Enemy_Fly::Update()
{
    transform_.rotate_.y += 0.5;    


}

//描画
void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Enemy_Fly::Release()
{
}