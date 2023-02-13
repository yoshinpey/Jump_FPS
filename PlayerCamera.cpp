#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"


//コンストラクタ
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1), pNum(nullptr), camPosX(0), camPosY(0)
{
    moveLength = XMFLOAT3{ 0,0,0 };
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
    transform_.position_.y = 5;
    transform_.position_.z =-10;

    //マウス座標テキスト
    pNum = new Text;
    pNum->Initialize();


}

//更新
void PlayerCamera::Update()
{
    //マウス移動量
    moveLength = Input::GetMouseMove();

    if (moveLength.x >= 0)
    {
        moveLength.x += transform_.rotate_.y * 0.1;
    }
    else
    {
        moveLength.x -= transform_.rotate_.y * 0.1;
    }


    Camera::SetTarget(moveLength);

    //違う。。。。。。。。。。。。。。
    //camPosX = Player::GetPlayerPositionX(camPosX);
    XMFLOAT3 camPos = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z);
    Camera::SetPosition(camPos);
}

//描画
void PlayerCamera::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //テキスト
    pNum->Draw(250, 100, moveLength.x);
    pNum->Draw(250, 200, moveLength.y * -1);  //表記を視覚的にわかりやすくするため上下反転にて表示
}

//開放
void PlayerCamera::Release()
{
}
