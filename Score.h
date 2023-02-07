#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Scoreを管理するクラス
class Score : public GameObject
{
    Text* pText;
public:
    //コンストラクタ
    Score(GameObject* parent);

    //デストラクタ
    ~Score();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};