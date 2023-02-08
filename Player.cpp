#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Player.h"


enum
{
    CAM_TYPE_FIXED,         //0　全体像固定
    CAM_TYPE_TPS_NO_ROT,    //1　三人称(回転なし)
    CAM_TYPE_TPS,           //2　三人称
    CAM_TYPE_FPS,           //3　一人称
    CAM_TYPE_MAX            //4　最後のカメラ　
};

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
    hModel_ = Model::Load("Character/Player.fbx");
    assert(hModel_ >= 0);
}

//更新
void Player::Update()
{
    PlayerMove();

    if (Input::IsKeyDown(DIK_V))
    {
        camType_++;
    }

    switch (camType_)
    {
    case CAM_TYPE_FIXED:
    {
        Camera::SetPosition(XMFLOAT3(0, 30, -100));
        Camera::SetTarget(XMFLOAT3(0, 0, 0));
        break;
    }

    case CAM_TYPE_TPS_NO_ROT:
    {
        Camera::SetTarget(transform_.position_);
        XMFLOAT3 camPos = transform_.position_;
        camPos.y += 10;
        camPos.z -= 20;
        Camera::SetPosition(camPos);
        break;
    }

    case CAM_TYPE_TPS:
    {
        Camera::SetTarget(transform_.position_);
        XMVECTOR vCam = { 0, 10, -20, 0 };
        vCam = XMVector3TransformCoord(vCam, mRotY);
        XMFLOAT3 camPos;
        XMStoreFloat3(&camPos, vPos + vCam);
        Camera::SetPosition(camPos);
        break;
    }

    case CAM_TYPE_FPS:
    {
        Camera::SetPosition(transform_.position_);
        XMFLOAT3 camTarget;
        XMStoreFloat3(&camTarget, vPos + vMove);
        Camera::SetTarget(camTarget);
        break;
    }

    case CAM_TYPE_MAX:
    {
        camType_ = 0;
        break;
    }
}

//描画
void Player::Draw()
{
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

    //移動入力がないときは向きを固定
    if (length != 0)
    {
        XMVECTOR vFront = { 0,0,1,0 };
        vMove = XMVector3Normalize(vMove);

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
}