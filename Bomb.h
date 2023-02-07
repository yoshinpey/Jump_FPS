#pragma once
#include "Engine/GameObject.h"

//Bombを管理するクラス
class Bomb : public GameObject
{
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    Bomb(GameObject* parent);

    //デストラクタ
    ~Bomb();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};