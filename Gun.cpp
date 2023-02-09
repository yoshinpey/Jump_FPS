#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Gun.h"
#include "Bullet.h"


//コンストラクタ
Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1), Bullet_speed(2)
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
    hModel_ = Model::Load("Entity/Rifle_re.fbx");
    assert(hModel_ >= 0);

    //プレイヤーの手の位置まで調整
    transform_.position_.y = 0.72;
    transform_.position_.x = 0.25;
    transform_.position_.z = 1.5;
}

//更新
void Gun::Update()
{
    //発砲
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //銃モデル先端
        XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
        //銃モデル根本
        XMFLOAT3 GunRoot = Model::GetBonePosition(hModel_, "Root");
        //ベクトルに変換
        XMVECTOR vTop = XMLoadFloat3(&GunTop);
        XMVECTOR vRoot = XMLoadFloat3(&GunRoot);
        //銃身長さ(方向含む)算出
        XMVECTOR vMove = vTop - vRoot;
        //正規化
        vMove = XMVector3Normalize(vMove);
        //vMove *= Bullet_speed;予定
        vMove *= Bullet_speed;
        //元に戻す
        XMFLOAT3 move;
        XMStoreFloat3(&move, vMove);
        //弾を呼ぶ      Gun->Player->PlayScene
        Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());
        //弾の位置
        pBullet->SetPosition(GunTop); // 主砲先端
        pBullet->SetMove(move);
    }
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