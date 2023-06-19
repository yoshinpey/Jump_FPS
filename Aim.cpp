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

   
}

//更新
void Aim::Update()
{ 
    Input::SetMousePosition(800/2, 600/2);//マウス初期位置(画面中央)
    //マウス移動量
    XMFLOAT3 mouseMove = Input::GetMouseMove(); // マウスの移動量を取得

    //移動量を加算
    transform_.rotate_.y += static_cast<float>(mouseMove.x) * 0.05f; // 横方向の回転
    transform_.rotate_.x += static_cast<float>(mouseMove.y) * 0.05f; // 縦方向の回転

    //プレイヤー座標取得
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();

    //プレイヤーキャラクターの位置をカメラの位置とする
    camPos.x = PlaPosX_;
    camPos.y = PlaPosY_ + 2; //目線高さ
    camPos.z = PlaPosZ_;

    //カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //カメラの位置と回転を合成
    XMMATRIX mView = mRotX * mRotY;

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

    //デバック用テキスト
    pNum->Draw(650, 400, "+");
    pNum->Draw(1100, 100, "X:   ");
    pNum->Draw(1150, 100, fPoint.x);
    pNum->Draw(1100, 200, "Y:   ");
    pNum->Draw(1150, 200, fPoint.y * -1);//表記を視覚的にわかりやすくするため上下反転表示
}

//開放
void Aim::Release()
{
}
