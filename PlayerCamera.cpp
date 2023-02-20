#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"
#include "Gun.h"


//コンストラクタ
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1),
    pNum(nullptr), PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0)
{
    XMFLOAT3 fMove = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 fPoint = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 camPos = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 plaPos_ = XMFLOAT3{ 0,0,0 };
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
    transform_.position_.y = 2;
    transform_.position_.z = 0;

    //マウス座標テキスト
    pNum = new Text;
    pNum->Initialize();

    //銃はカメラにつく
    Instantiate<Gun>(this);

    Input::SetMousePosition(300, 250);//マウス初期位置(画面中央)
}

//更新
void PlayerCamera::Update()
{
    
    //マウス移動量
    fPoint = Input::GetMouseMove();

    //プレイヤー座標取得
    Player* pPlayer = (Player*)FindObject("Player");
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();

    //マウス位置保存用変数
    float Px=0,Py=0;

    //移動量を加算
    Px += fPoint.x;     
    Py += fPoint.y;
    //回転移動に反映
    transform_.rotate_.y += Px *0.05;
    transform_.rotate_.x += Py *0.05;





    //視点ができない！！！！！
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMove = { 0.0f, 0.0f, 0.3f, 0.0f, };
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    vMove = XMVector3TransformCoord(vMove, mRotY*mRotX);

    camPos.x = transform_.position_.x;
    camPos.y = transform_.position_.y;
    camPos.z = transform_.position_.z;

    Camera::SetPosition(camPos);
    XMFLOAT3 PlayerHead;
    XMStoreFloat3(&PlayerHead, vPos + vMove);
    Camera::SetTarget(PlayerHead);

    //XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    //Camera::SetTarget(GunTop);



}

//描画
void PlayerCamera::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //デバック用テキスト
    pNum->Draw(650, 400, "+");
    pNum->Draw(1100, 100, "X:   ");
    pNum->Draw(1150, 100,  fPoint.x);
    pNum->Draw(1100, 200, "Y:   ");
    pNum->Draw(1150, 200, fPoint.y * -1);//表記を視覚的にわかりやすくするため上下反転表示
}

//開放
void PlayerCamera::Release()
{
}
