#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"


//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),
    gravity_(-0.1), jumpGauge(50),jumpCool(0), CanJump_(false), jumpVel(0.2), jumpTime(0),
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
    //Jump();             //ジャンプアクション
    //JetPack();          //ブーストアクション
    BoostJump();
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

//視点
void Player::CameraPosition()
{
#if 0
    //テスト用のカメラ
    XMFLOAT3 camPos{ 0, 10, -20 };
    XMFLOAT3 camTag{ 0, 0, 0 };
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTag);
#endif
}


// プレイヤーの移動
void Player::Move()
{
    // 移動
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    // エイム情報呼び出し
    Aim* pAim = (Aim*)FindObject("Aim");
    XMFLOAT3 aimDirection = pAim->GetAimDirection();

    // PlayerクラスのMove関数内の一部
    if (Input::IsKey(DIK_W)) {
        fMove.x += aimDirection.x;
        fMove.z += aimDirection.z;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x -= aimDirection.z;
        fMove.z += aimDirection.x;
    }
    if (Input::IsKey(DIK_S)) {
        fMove.x -= aimDirection.x;
        fMove.z -= aimDirection.z;
    }
    if (Input::IsKey(DIK_D)) {
        fMove.x += aimDirection.z;
        fMove.z -= aimDirection.x;
    }

    // 正規化する
    float moveLength = sqrtf(fMove.x * fMove.x + fMove.z * fMove.z);
    if (moveLength != 0)
    {
        fMove.x /= moveLength;
        fMove.z /= moveLength;
    }

    // 速度の制御
    float walkSpeed = 0.2f;         // 歩行速度
    float runSpeed = 0.4f;          // 走行速度
    float nowSpeed = 0;             // 初期速度

    // 移動入力があるかどうか
    bool isMoving = Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D);

    // 移動入力あり
    if (isMoving)
    {
        // 走っているかどうか
        if (Input::IsKey(DIK_LSHIFT))
        {
            nowSpeed = runSpeed;    // 走り速度を設定
        }
        else
        {
            nowSpeed = walkSpeed;   // 歩き速度を設定
        }
    }
    else
    {
        // 各移動ボタンを離したときに速度をリセット
        nowSpeed = 0.0f;
    }

    // 移動に反映
    transform_.position_.x += fMove.x * nowSpeed;
    transform_.position_.z += fMove.z * nowSpeed;
}


#if 0
void Player::BoostJump()
{
    ///////////とりあえずの構想////////////////////
    static int jumpCount = 0;              // ジャンプ回数
    if (Input::IsKey(DIK_SPACE))            // ジャンプキーが押された場合
    {
        if (jumpCount == 0)                 // ジャンプ回数が0の場合（通常のジャンプ）
        {
            // 通常のジャンプ処理
            Jump();
            jumpCount = 1;                  // ジャンプ回数を1に設定
        }
        else if (jumpCount == 1)            // ジャンプ回数が1の場合（ブーストジャンプ）
        {
            // ブーストジャンプ処理
            JetPack();
            jumpCount = 0;                  // ジャンプ回数をリセット
        }
    }
    // 地面に着地した場合の処理
    if (transform_.position_.y <= 0)
    {
        transform_.position_.y = 0;
    }
}
#endif


void Player::BoostJump()
{
    /////////////////////////////////////////////////////////////////工事中//////////////
    float velocity = 5.0f;          // 初速度
    float gravity = -9.8f;          // 重力加速度
    float deltaTime = 0.019f;       // 適当なごく小さい値

    static bool canJump = true;     // ジャンプ可能な状態かどうか
    static float jumpTime = 0.0f;   // ジャンプ経過時間

    if (Input::IsKeyDown(DIK_SPACE) && canJump) //ジャンプキーが押されており、ジャンプ可能な場合
    {
        jumpTime = 0.0f;
        canJump = false;  //連続ジャンプを防止するため、ジャンプ中はジャンプフラグを無効化
    }

    if (!canJump)
    {
        //ジャンプしてからの時間の経過
        jumpTime += deltaTime;

        //鉛直投げ上げ運動    y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * jumpTime + 0.5f * gravity * jumpTime * jumpTime;
        transform_.position_.y = pos;

        //重力による落下
        velocity += gravity * deltaTime;

        //地面に着地したとき
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;
            canJump = true;  // 地面に着地したらジャンプ可能にする
        }
    }
}

void Player::JetPack()
{

    //重力 => 座標が0より大きい時に働く
    if (transform_.position_.y > 0)
        transform_.position_.y += gravity_;

    //ジャンプフラグ----ゲージが0より大きい時ジャンプ可能
    if (jumpGauge > 0)
        CanJump_ = true;

    //ジャンプ可能な時の処理
    if (CanJump_)
    {
        if (Input::IsKey(DIK_SPACE))        //ジャンプキー
        {
            jumpTime += 0.01;
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
        CanJump_ = false;                   //ジャンプ不可
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


//ジャンプ
void Player::Jump()
{
    float velocity = 5.0f;          // 初速度
    float gravity = -9.8f;          // 重力加速度
    float deltaTime = 0.019f;       // 適当なごく小さい値

    static bool canJump = true;     // ジャンプ可能な状態かどうか
    static float jumpTime = 0.0f;   // ジャンプ経過時間

    if (Input::IsKeyDown(DIK_SPACE) && canJump) //ジャンプキーが押されており、ジャンプ可能な場合
    {
        jumpTime = 0.0f;
        canJump = false;  //連続ジャンプを防止するため、ジャンプ中はジャンプフラグを無効化
    }

    if (!canJump)
    {
        //ジャンプしてからの時間の経過
        jumpTime += deltaTime;
        
        //鉛直投げ上げ運動    y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * jumpTime + 0.5f * gravity * jumpTime * jumpTime;
        transform_.position_.y = pos;

        //重力による落下
        velocity += gravity * deltaTime;

        //地面に着地したとき
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;
            canJump = true;  // 地面に着地したらジャンプ可能にする
        }
    }
}