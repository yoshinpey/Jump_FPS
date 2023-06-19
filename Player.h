#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;                            //モデル番号   
    int maxHp_, nowHp_;                     //HP 
    bool CanJump;                           //ジャンプ可能か
    float gravity_, jumpGauge, jumpCool,    //重力、ジャンプゲージ、リチャージ時間
          jumpVel, jumpTime;                //ジャンプ力、加速度変化用タイマー
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //プレイヤー座標
   
    Text* pNum;
public:
    Player(GameObject* parent);     //コンストラクタ
    ~Player();                      //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放
    
    //アクション
    void Move();                    //プレイヤーの移動
    void Jump();                    //ジャンプ
    void PlayerHitPoint();          //体力
    void CameraPosition();          //視点

    //プレイヤー座標のゲッター
    float GetPlaPosX() { return transform_.position_.x; }
    float GetPlaPosY() { return transform_.position_.y; }
    float GetPlaPosZ() { return transform_.position_.z; }
};