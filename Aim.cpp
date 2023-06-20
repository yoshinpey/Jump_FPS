#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Player.h"
#include "Gun.h"


//コンストラクタ
Aim::Aim(GameObject* parent)
    :GameObject(parent, "Aim"), pNum(nullptr),
    PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0),
    camPos{ 0,0,0 }, camTarget{ 0,0,0 }, fPoint{ 0,0,0 },
    vPos{ 0,0,0,0 }, vMove{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

//デストラクタ
Aim::~Aim()
{
}

//初期化
void Aim::Initialize()
{
    transform_.position_.y = 2;

    //マウス座標テキスト
    pNum = new Text;
    pNum->Initialize();

    //銃はカメラにつく
    Instantiate<Gun>(this);

       Input::SetMousePosition(800/2, 600/2);//マウス初期位置(画面中央)
}

//更新
void Aim::Update()
{ 
    //マウス移動量
    XMFLOAT3 mouseMove = Input::GetMouseMove(); // マウスの移動量を取得

    //移動量を加算
    transform_.rotate_.y += (mouseMove.x) * 0.05f; // 横方向の回転
    transform_.rotate_.x += (mouseMove.y) * 0.05f; // 縦方向の回転

    ////カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); 
    //カメラの位置と回転を合成
    XMMATRIX mView = mRotX * mRotY;

    XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forwardVector = XMVector3TransformCoord(forwardVector, mView);
    XMStoreFloat3(&aimDirection_, forwardVector);

    //プレイヤー座標取得
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();

    //プレイヤーキャラクターの位置をカメラの位置とする
    camPos.x = PlaPosX_;
    camPos.y = PlaPosY_ + 2; //目線高さ
    camPos.z = PlaPosZ_;

    //カメラの位置と焦点を取得
    XMVECTOR camPosVector = XMLoadFloat3(&camPos);
    XMVECTOR camTarget = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    camTarget = XMVector3TransformCoord(camTarget, mView);
    camTarget = XMVectorAdd(camPosVector, camTarget);

    //カメラの位置と焦点を設定
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, camTarget);
    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}


//描画
void Aim::Draw()
{
    pNum->Draw(650, 400, "+");
}

//開放
void Aim::Release()
{
}
