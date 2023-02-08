#pragma once
#include "Engine/GameObject.h"

//Playerを管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号
    int camType_;
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
};