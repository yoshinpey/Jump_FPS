#pragma once
#include "Engine/GameObject.h"
//Playerの子供
//銃を管理するクラス
class Gun : public GameObject
{
    int hModel_;    //モデル番号
    float Bullet_speed;
public:
    //コンストラクタ
    Gun(GameObject* parent);

    //デストラクタ
    ~Gun();
    
    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};