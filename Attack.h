#pragma once
#include "Engine/GameObject.h"

//近接攻撃を管理するクラス
class Attack : public GameObject
{
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    Attack(GameObject* parent);

    //デストラクタ
    ~Attack();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};