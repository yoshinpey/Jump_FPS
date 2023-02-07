#pragma once
#include "Engine/GameObject.h"

//Crystalを管理するクラス
class Crystal : public GameObject
{
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    Crystal(GameObject* parent);

    //デストラクタ
    ~Crystal();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};