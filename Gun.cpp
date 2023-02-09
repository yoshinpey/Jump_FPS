#include "Engine/Model.h"

#include "Gun.h"


//コンストラクタ
Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1)
{
}

//デストラクタ
Gun::~Gun()
{
}

//初期化
void Gun::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Entity/Rifle_mini.fbx");
    assert(hModel_ >= 0);

    transform_.position_.y = 0.72;
    transform_.position_.x = 0.25;
    transform_.position_.z = 1.5;
}

//更新
void Gun::Update()
{
}

//描画
void Gun::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Gun::Release()
{
}