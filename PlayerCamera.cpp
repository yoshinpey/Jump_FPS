#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"
#include "Gun.h"


//コンストラクタ
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1), pNum(nullptr)
{
    XMFLOAT3 fMove = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 fPoint = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 camPos = XMFLOAT3{ 0,0,0 };
}

//デストラクタ
PlayerCamera::~PlayerCamera()
{
}

//初期化
void PlayerCamera::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Character/PlayerCamera.fbx");
    assert(hModel_ >= 0);
    transform_.position_.x = 0;
    transform_.position_.y = 3;
    transform_.position_.z = -1;

    //マウス座標テキスト
    pNum = new Text;
    pNum->Initialize();

    //銃はカメラの向く方向へ動かす
    Instantiate<Gun>(this);
}

//更新
void PlayerCamera::Update()
{
    //マウス移動量
    fPoint = Input::GetMouseMove();

    //ポイントセット
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMove = { 0.0f, 0.0f, 0.3f, 0.0f, };//奥に0.3移動
    

    XMVECTOR vPoint = XMLoadFloat3(&fPoint);
    XMVECTOR vPoint2 = XMLoadFloat3(&fPoint2);
    XMVECTOR vMove = vPoint - vPoint2;

    //vMove = XMVector3Normalize(vMove);
    //vMove *= 0.3;

    Camera::SetPosition(transform_.position_);

    XMFLOAT3 camTarget;
    XMStoreFloat3(&camTarget, vPoint + vMove);
    Camera::SetTarget(camTarget);

    //カメラを頭に位置にセット
    camPos = transform_.position_;
    
}

//描画
void PlayerCamera::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //テキスト
    pNum->Draw(250, 100, fPoint.x);
    pNum->Draw(250, 200, fPoint.y * -1);  //表記を視覚的にわかりやすくするため上下反転にて表示
}

//開放
void PlayerCamera::Release()
{
}
