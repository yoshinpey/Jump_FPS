#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
//#include "Gravity.h"
#include "Player.h"
#include "Gauge.h"



//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), Gravity_(-0.1), 
    PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0), maxHp_(100), nowHp_(100),jumpCool(0),jumpTime(5)//, CanJump(true)
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

    //カメラ
    Instantiate<Aim>(this);

    pNum = new Text;
    pNum->Initialize();

}

//更新
void Player::Update()
{

    PlayerMove();

    CameraPosition();

    PlayerHitPoint();

 
    //ジャンプ

    if (transform_.position_.y > 0)
    {
        transform_.position_.y -= 0.1;
    }
    else if(jumpCool >= 0)
        jumpCool--;


    if (jumpCool <= 0)
    {
        if (Input::IsKey(DIK_SPACE))
        {
            transform_.position_.y += 0.3;
            jumpTime--;
        }
    }
    if (jumpTime == 0)
    {
        jumpCool = 60;
    }
    

}

//描画
void Player::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    pNum->Draw(500, 100, jumpCool);
    pNum->Draw(500, 300, jumpTime);
}

//開放
void Player::Release()
{
}

//プレイヤーのHP
void Player::PlayerHitPoint()
{
    //HP
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(maxHp_, nowHp_);

    //エラー潰し
    if (Input::IsKeyDown(DIK_M))
    {
        nowHp_ += 20;
        if (nowHp_ > maxHp_)
        {
            nowHp_ = maxHp_;
        }
    }
    if (Input::IsKeyDown(DIK_N))
    {
        nowHp_ -= 20;
        if (nowHp_ < 0)
        {
            nowHp_ = 0;
        }
    }
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
    
    //移動量を一定に調整
    XMVECTOR vMove;
    vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    vMove *= 0.1f;
    XMStoreFloat3(&fMove, vMove);

    //移動に反映
    transform_.position_.x += fMove.x;
    transform_.position_.z += fMove.z;


}

//視点
void Player::CameraPosition() 
{

    //test
    //Camera::SetPosition();
}



