#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Player.h"
#include "Gun.h"


//コンストラクタ
Aim::Aim(GameObject* parent)
    :GameObject(parent, "Aim"), pNum(nullptr),
    plaPos_{0,0,0},camPos{ 0,0,0 }, camTarget{ 0,0,0 }
{
}

//デストラクタ
Aim::~Aim()
{
}

//初期化
void Aim::Initialize()
{
    //エイムクラスの呼び出し位置
    transform_.position_.y = 2;

    //マウス座標テキスト
    pNum = new Text;
    pNum->Initialize();

    //銃はカメラにつく
    Instantiate<Gun>(this);

    //マウス初期位置(幅/2, 高さ/2)
    Input::SetMousePosition(800/2, 600/2);
}

//更新
void Aim::Update()
{ 
    /*/////////////////////////////////////////このために数学を勉強し直しました。
    ----------------------------
    //初めのマウス位置座標を取得
    XMFLOAT3 firstMousePos_ = Input::GetMousePosition();
    ------------------------------

    //現在のマウス位置座標を取得
    XMFLOAT3 mousePos_ = Input::GetMousePosition();

    //移動ベクトル ＝ 初期位置 - 現在地
    float deltaX = firstMousePos_.x - mousePos_.x;
    float deltaY = firstMousePos_.y - mousePos_.y;

    //向きを算出
    direction_ = -(float)atan2(deltaX, deltaY);
    /////////////////////////////////////////////////*/
    
    //////////////////////////////////////あるいは、、、、、、
    //マウスの移動量を取得
    XMFLOAT3 mouseMove = Input::GetMouseMove();
    
    //移動ベクトルの長さを計算------3平方の定理------
    float moveLength = sqrtf(mouseMove.x * mouseMove.x + mouseMove.y * mouseMove.y);

    //方向ベクトルを計算-----正規化-----
    XMFLOAT3 fDirection{};
    fDirection.x = mouseMove.x / moveLength;
    fDirection.y = mouseMove.y / moveLength;
    fDirection.z = 0.0f;

    //移動量を加算
    transform_.rotate_.y += (fDirection.x) * 5.0f; // 横方向の回転
    transform_.rotate_.x += (fDirection.y) * 5.0f; // 縦方向の回転

    //////////////////////////////////////でもやっぱ、せっかくだしカッコよく書きたい！


    /*//////////////////////////////////
    //マウスの移動量を取得
    XMFLOAT3 mouseMove = Input::GetMouseMove();

    //移動ベクトルを計算
    XMVECTOR moveVector = XMLoadFloat3(&mouseMove);

    //方向ベクトルを正規化
    XMVECTOR normalizedDirection = XMVector3Normalize(moveVector);

    //正規化された方向ベクトルを取得
    XMFLOAT3 fDirection;
    XMStoreFloat3(&fDirection, normalizedDirection);

    //移動量を加算
    transform_.rotate_.y += (fDirection.x) * 5.0f; // 横方向の回転
    transform_.rotate_.x += (fDirection.y) * 5.0f; // 縦方向の回転

    //////////////////////////////////////////////////一見良さげだけどだめでした。。*/

    ////カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); 

    //カメラの位置と回転を合成
    XMMATRIX mView = mRotX * mRotY;

    //プレイヤー座標取得
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    plaPos_ = pPlayer->GetPlaPos();

    //プレイヤーキャラクターの位置をカメラの位置とする
    camPos.x = plaPos_.x;
    camPos.y = plaPos_.y + 2; //目線高さ
    camPos.z = plaPos_.z;

    //カメラの位置と焦点を取得
    XMVECTOR camPosVector = XMLoadFloat3(&camPos);
    XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forwardVector = XMVector3TransformCoord(forwardVector, mView);
    XMStoreFloat3(&aimDirection_, forwardVector);   //プレイヤークラスに進行方向ベクトル(float3)を伝える用                    
    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    //カメラの位置と焦点を設定
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);
    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);

}

//描画
void Aim::Draw()
{
    pNum->Draw(1520/2, 800/2, "+");
}

//開放
void Aim::Release()
{
}
