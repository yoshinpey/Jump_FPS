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
    hModel_ = Model::Load("ファイル名");
    assert(hModel_ >= 0);
}

//更新
void Enemy_Fly::Update()
{
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