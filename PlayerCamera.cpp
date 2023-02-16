#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"
#include "Gun.h"


//コンストラクタ
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1), pNum(nullptr), PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0)
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
}

//更新
void PlayerCamera::Update()
{
    //マウス移動量
    fPoint = Input::GetMouseMove();

    Player* pPlayer = (Player*)FindObject("Player");
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();


}

//描画
void PlayerCamera::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //デバック用テキスト
    pNum->Draw(250, 100, fPoint.x);
    pNum->Draw(250, 200, fPoint.y * -1);  //表記を視覚的にわかりやすくするため上下反転表示
}

//開放
void PlayerCamera::Release()
{
}
