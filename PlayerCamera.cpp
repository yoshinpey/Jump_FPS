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
        if (XMVectorGetY(vCross) < 0)
        {
            angle *= -1;
        }

        //デグリーに変換　
        transform_.rotate_.y = XMConvertToDegrees(angle);
        //ちなみに  　XMConvertToRadians()      <--ラジアンに変換180°＝ラジアン
    }
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
