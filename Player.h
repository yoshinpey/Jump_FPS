#pragma once
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;                            //モデル番号   
    int maxHp_, nowHp_;                     //HP
    bool jumpReady;
    float Gravity_;
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //プレイヤー座標
    double jumpTime;
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
    float GetPlaPosX() { return PlaPosX_ = transform_.position_.x; }
    float GetPlaPosY() { return PlaPosY_ = transform_.position_.y; }
    float GetPlaPosZ() { return PlaPosZ_ = transform_.position_.z; }
};