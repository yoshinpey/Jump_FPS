#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;        //モデル番号   
    int maxHp_, nowHp_; //HP 
    bool CanJump_;       //ジャンプ可能か
    float gravity_;     //重力

    float jumpGauge;    //滞空可能時間
    float jumpCool;     //リチャージ時間
    float jumpVel;      //ジャンプ力
    float jumpTime;     //加速度変化用タイマー

    Text* pNum;         //テキスト

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
    XMFLOAT3 GetPlaPos() { return transform_.position_; }

};