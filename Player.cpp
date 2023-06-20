#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"



//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),
    gravity_(-0.1), jumpGauge(50),jumpCool(0), CanJump(false), jumpVel(0.2), jumpTime(0),
    maxHp_(100), nowHp_(100)
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

    //視点クラス読み込み
    Instantiate<Aim>(this);

    //テキスト
    pNum = new Text;
    pNum->Initialize();
}

//更新
void Player::Update()
{
    Move();             //動き
    CameraPosition();   //視点
    PlayerHitPoint();   //HP

}

//描画
void Player::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //デバック用テキスト
    pNum->Draw(50, 200, "jumpGauge");
    pNum->Draw(50, 250, jumpGauge);
    pNum->Draw(50, 400, "jumpCool");
    pNum->Draw(50, 450, jumpCool);

    pNum->Draw(1150, 100, "X:");
    pNum->Draw(1200, 100, transform_.position_.x);
    pNum->Draw(1150, 250, "Y:");
    pNum->Draw(1200, 250, transform_.position_.y);
    pNum->Draw(1150, 400, "Z:");
    pNum->Draw(1200, 400, transform_.position_.z);
}

//開放
void Player::Release()
{
}

//プレイヤーのHP
void Player::PlayerHitPoint()
{
    //HPゲージ呼び出し
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
void Player::Move() 
{
    //移動
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    //エイム情報呼び出し
    Aim* pAim = (Aim*)FindObject("Aim");

    // PlayerクラスのMove関数内の一部
    if (Input::IsKey(DIK_W)) {
        fMove.x = pAim->GetAimDirection().x;
        fMove.z = pAim->GetAimDirection().z;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x = pAim->GetAimDirection().z;
        fMove.z = -pAim->GetAimDirection().x;
    }
    if (Input::IsKey(DIK_S)) {
        fMove.x = -pAim->GetAimDirection().x;
        fMove.z = -pAim->GetAimDirection().z;
    }
    if (Input::IsKey(DIK_D)) {
        fMove.x = -pAim->GetAimDirection().z;
        fMove.z = pAim->GetAimDirection().x;   
    }

    
    //移動量を一定に調整
    // 移動ベクトルをAimコンポーネントの回転情報に合わせて変換
    XMFLOAT3 forward = pAim->GetAimDirection();
    XMVECTOR vMove = XMLoadFloat3(&fMove);
    XMVECTOR rotatedMove = XMVector3Rotate(vMove, XMLoadFloat3(&forward));
    XMStoreFloat3(&fMove, rotatedMove);

    // 移動に反映
    transform_.position_.x += fMove.x*0.3;
    transform_.position_.z += fMove.z*0.3;


    //ジャンプアクション
    Jump();
}

//ジャンプ
void Player::Jump()
{
    //重力 => 座標が0より大きい時に働く
    if (transform_.position_.y > 0)
        transform_.position_.y += gravity_;

    //ジャンプフラグ----ゲージが0より大きい時ジャンプ可能
    if (jumpGauge > 0)
        CanJump = true;

    //ジャンプ可能な時の処理
    if (CanJump)
    {
        if (Input::IsKey(DIK_SPACE))        //ジャンプキー
        {
            if (jumpTime <= 1)              //加速限界以下だったら
            {
                jumpTime += 0.01;
            }
            jumpGauge--;
            transform_.position_.y += (jumpVel + jumpTime);
        }
        else
        {
            jumpTime = 0;                   //キー入力がなければジャンプタイムを0にする
        }
    }

    //ジャンプ不可能になる条件--ゲージが0以下
    if (jumpGauge <= 0)
    {
        CanJump = false;                    //ジャンプ不可
        if (jumpCool <= 0)                  //クールタイムを設定
            jumpCool += 30;                 //再使用可能(回復待機)時間
    }

    //クールタイムは0まで減らす
    if (jumpCool > 0)
    {
        jumpCool--;
    }

    //ジャンプ不可能な時の処理--ゲージはY座標が0の時のみ回復
    if (transform_.position_.y <= 0 && jumpCool <= 0)//クールタイムが無くなってから増やす
    {
        if (jumpGauge < 50)//ゲージの最大値まで
        {
            jumpGauge++;
        }
    }
}

//視点
void Player::CameraPosition() 
{
    /*テスト用のカメラ
    XMFLOAT3 camPos{ 0, 10, -20 };
    XMFLOAT3 camTag{ 0, 0, 0 };
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTag);*/
}
