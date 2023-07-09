#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"

/*
<今思いついてるやることリスト>

//player
当たり判定作るの忘れてた
---コライダーつける。
モデルが回転してない
---頭クラス(腕もつける？)とか作ってそっちにカメラつけたほうがいいかもしれん
HPゲージの実装する
---今まだ銃のダメージ判定とかできてないから後でやろう
ジェットパックのコード汚すぎるから直す
---上昇の加速が微妙。自然落下するときの挙動もなんか変。あとゲージも出したいな
通常ジャンプとジェットパックの掛け合わせ
---あとでやる。
歩きと走りに加速を付ける
---色々試したけど結構むずい気がする
移動入力をやめたときピタッと止まるの直す
---加速ができれば自ずとできるかなって思ってる
逆キーを入力したら慣性の法則が働く感じにしたい
---同上
しゃがみ作りたい
---モデル差し替えて判定を半分にするだけ
スライディング作りたい
---やはりプレイヤーの頭と体を一緒にしたのが間違いかもしれない・・・・
---カメラをどうするかが課題。今の目線のまま体を横にしてスライディングしたらおそらくバグる
---スライディング中は固定カメラにしちゃおうか・・・？あるいはクラスを分ければいいかも

//gun
当たり判定をレイキャストにするか、もしくはノズルの先端からコライダーを伸ばして判定を作るとかやりたい。
今の異状態だと弾抜けとかあるし、本場のFPSプレイヤーなら台パン不可避。着弾スピードが遅いのもストレス

//bomb
モデル追加して時間経過で適当にサウンドとエフェクト再生してコライダー広げればいいかな

//winmain
スクリーンの座標取得でスクリーンサイズをディスプレイサイズに合わせたい

//各シーン
それぞれ画像用意したりなんか動きつけたりしたい
---タイマーとかスコアの反映とかも考えねば

//enemy
近づいて爆発してくる敵を作る
---経路探索の実装が正直よくわかってない
---壁を避けるやつとか前に誰か作ってたよな教えてほちい
---胴体と頭で別の判定付けてダメージ倍率変えたい
空飛んで遠距離攻撃を売ってくる敵を作る
---玉っころとかレーザービーム
---せっかく自分も空飛べるから、プレイヤーから一定の距離保って攻撃して来るとかやりたい
---弾除けとかするようにできたら極悪過ぎて最高

//クリスタル
スコアアップアイテムにするか殲滅スキルにするか未定

//
*/

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),
    gravity_(-9.81), maxFuel_(50), fuel_(0), coolTime_(0), CanJump_(false), acceleration_(0.5),
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
    Move();                 //動き
    //Jump();               //ジャンプアクション
    JetPack();              //ジェットパック
    //BoostJump();          //ブーストジャンプ
    CameraPosition();       //視点
    PlayerHitPoint();       //HP
}

//描画
void Player::Draw()
{
    //モデル
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //デバック用テキスト
    pNum->Draw(50, 200, "fuel");
    pNum->Draw(50, 250, fuel_);
    pNum->Draw(50, 400, "coolTime");
    pNum->Draw(50, 450, coolTime_);

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



#if 1
//実装できたけど挙動が早すぎてキモい
void Player::JetPack()
{
    float gravity = -9.81f;      // 重力
    float delta = 0.02f;         // 適当なごく小さい値
    float velocity = 0.0f;       // 初速度
    float flightTime = 0.0f;     // 滞空中の時間経過

    bool onGround = transform_.position_.y <= 0;   // 地面にいるとき
    bool hasHuel = fuel_ > 0;                       // 燃料があるとき

    if (!onGround)
    {
        // 自由落下
        transform_.position_.y += gravity * delta + delta;
    }

    // ジャンプ可能--燃料が0より大きい時
    if (hasHuel)
    {
        if (Input::IsKey(DIK_SPACE)) 
        {
            flightTime++;
            velocity = acceleration_ * flightTime;
            transform_.position_.y += velocity;     // 位置＝初速度*経過時間
            fuel_--;                                // 燃料を減らす
        }
    }
    else
    {
        flightTime = 0.0f;      // キー入力がなければ時間加速率をリセット
    }

    // ジャンプ不可能--地面にいるかつ燃料がカラ
    if (onGround && !hasHuel)
    {    
        transform_.position_.y = 0.0f;
        if (coolTime_ <= 0.0f)
            coolTime_ += 20.0f;             // わずかな回復待機時間を用意
    }

    if (coolTime_ > 0.0f) 
        coolTime_--;        // クールタイムが残っていたら0になるまで減らす

    //ジャンプ不可能--地面にいるかつクールタイム中
    if (onGround && coolTime_ <= 0)
    {
        if (fuel_ < maxFuel_)         //ゲージの最大値まで
            fuel_++;
    }
}
#endif

//前に書いた仕組みダサいけど一応動いてるboost
#if 0
void Player::JetPack()
{
    float velocity = 1.0f;      // ジャンプ力
    float flightTime = 0.0f;    // 滞空中の時間経過
    float gravity = -0.3f;      // 重力
    float fallTime = 0.0f;      // 落下時間

    bool onGround = transform_.position_.y <= 0;   // 地面にいるとき
    bool hasHuel = fuel_ > 0;                       // 燃料があるとき

    // 重力は空中にいるときのみ働く
    if(!onGround) transform_.position_.y += gravity + fallTime;

    // ジャンプ可能な時
    if(hasHuel)
    {
        if (Input::IsKey(DIK_SPACE)) // ジャンプキー入力したら
        {
            if (flightTime <= 1) flightTime += 0.1;            //加速限界まで徐々に加速
            transform_.position_.y += (velocity + flightTime);  //速度にジャンプ時間を加える
            fuel_--;                                            //燃料を減らす
        }
        else
        {
            flightTime = 0; //キー入力がなければ経過時間(加速)をリセット
            fallTime *= 1.1;
        }
    }
    else
    {
        if (coolTime_ <= 0) coolTime_ += 30; //わずかな燃料回復遅延を設定
    }

    // クールタイムを0まで減らす
    if (coolTime_ > 0)   coolTime_--;

    // 燃料は地面にいてクールタイム中でないときに回復
    if (onGround && coolTime_ <= 0)
    {
        if (fuel_ < 50) fuel_++; // 燃料を最大値まで回復
    }
}
#endif

//初期段階の組み合わせ構想、骨組み
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

//判定のメモ
#if 0
// 地面にいるか判定
bool isOnGround = transform_.position_.y <= 0.0f;

// ジャンプ入力を受け付ける条件
bool canJump = fuel > 0 && isOnGround;

// ジャンプ入力
if (Input::IsKey(DIK_SPACE) && canJump)
{
    velocity += acceleration * delta;  // 上昇速度を増加させる
    fuel--;                           // 燃料を減らす
}
else
{
    velocity = 0.0f;  // 上昇速度をリセット
}

// 自由落下
if (!isOnGround)
{
    velocity += gravity * delta;        // 重力による下降速度を追加
}

// 位置の更新
transform_.position_.y += velocity * delta;
#endif

//通常ジャンプ
void Player::Jump()
{
    float velocity = 5.0f;              // 初速度
    float delta = 0.02f;                // 適当なごく小さい値
    float gravity = 9.81;               // 
    static bool canJump = true;         // ジャンプ可能な状態かどうか
    static float flightTime = 0.0f;     // ジャンプ経過時間

    if (Input::IsKeyDown(DIK_SPACE) && canJump) //ジャンプキーが押されており、ジャンプ可能な場合
    {
        flightTime = 0.0f;
        canJump = false;                // 連続ジャンプを防止するため、ジャンプ中はジャンプフラグを無効化
    }

    if (!canJump)
    {
        //ジャンプしてからの時間の経過
        flightTime += delta;
        
        //鉛直投げ上げ運動          y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * flightTime + 0.5f * gravity * flightTime * flightTime;
        transform_.position_.y = pos;

        //重力による落下
        velocity += gravity * delta;

        //地面に着地したとき
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;     // 念のため地面に合わせる
            canJump = true;                 // 地面に着地したらジャンプ可能にする
        }
    }
}

