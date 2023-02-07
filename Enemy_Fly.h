#pragma once
#include "Engine/GameObject.h"

//Enemy_Flyを管理するクラス
class Enemy_Fly : public GameObject
{
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    Enemy_Fly(GameObject* parent);

    //デストラクタ
    ~Enemy_Fly();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};