#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;                            //モデル番号   
    int TheZERO;                            //無意味な変数。ゼロ。
    int maxHp_, nowHp_;                     //HP 
    bool CanJump;                           //ジャンプ可能
    float Gravity_, jumpGauge, jumpCool,    //重力、ジャンプゲージ、リチャージ時間
          jumpVel, jumpTime;                //ジャンプ力、加速度変化用タイマー
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //プレイヤー座標
   
    Text* pNum;
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //プレイヤー移動
    void PlayerMove();

    //プレイヤーHP
    void PlayerHitPoint();

    //カメラ
    void CameraPosition();

    //ジャンプ


    //プレイヤー座標のゲッター
    float GetPlaPosX() { return transform_.position_.x; }
    float GetPlaPosY() { return transform_.position_.y; }
    float GetPlaPosZ() { return transform_.position_.z; }
};