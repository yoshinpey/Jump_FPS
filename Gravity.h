#pragma once
#include "Engine/GameObject.h"

//  重力を管理するクラス
class Gravity : public GameObject
{
    bool Active;
    float gravity_;
public:
    //コンストラクタ
    Gravity(GameObject* parent);

    //デストラクタ
    ~Gravity();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //重力有効
    void GravityON();

    //重力無効
    void GravityOFF();
};