#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"
#include "Gun.h"


//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1)
{

}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Character/Human_only.fbx");
    assert(hModel_ >= 0);

    //銃を登場させる
    Instantiate<Gun>(this);

    //カメラ
    Instantiate<PlayerCamera>(this);


}

//更新
void Player::Update()
{

    PlayerMove();

    CameraPosition();

}

//描画
void Player::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

//プレイヤーの移動
void Player::PlayerMove() 
{
    //移動
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    if (Input::IsKey(DIK_W)){
        fMove.z = 1.0f;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x = -1.0f;
    }
    if (Input::IsKey(DIK_S)){
        fMove.z = -1.0f;
    }
    if (Input::IsKey(DIK_D)){
        fMove.x = 1.0f;
    }

    XMVECTOR vMove;
    vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    vMove *= 0.1f;
    XMStoreFloat3(&fMove, vMove);

    transform_.position_.x += fMove.x;
    transform_.position_.z += fMove.z;

    //向き変更  
    XMVECTOR vLength = XMVector3Length(vMove);
    float length = XMVectorGetX(vLength);
    //ベクトル
    XMVECTOR vFront = { 0,0,1,0 };
    vMove = XMVector3Normalize(vMove);

    //移動入力がないときは向きを固定
    if (length != 0)
    {
        //内積
        XMVECTOR vDot = XMVector3Dot(vFront, vMove);
        float dot = XMVectorGetX(vDot);
        float angle = acos(dot);
        //外積
        XMVECTOR vCross = XMVector3Cross(vFront, vMove);
        if (XMVectorGetY(vCross) < 0){
            angle *= -1;
        }
        //デグリーに変換　
        transform_.rotate_.y = XMConvertToDegrees(angle);
    }
    PlaPosX_ += transform_.position_.x;
    PlaPosZ_ += transform_.position_.z;
}

//視点
void Player::CameraPosition() 
{
    //とりあえずのカメラ
    //XMFLOAT3 camPos = XMFLOAT3(transform_.position_.x, 8, transform_.position_.z);
    //Camera::SetPosition(camPos);
    
    //マウスに連動する視点を作りたい！！

}

