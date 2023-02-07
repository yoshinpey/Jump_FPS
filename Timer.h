#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Timer管理するクラス
class Timer : public GameObject
{
    Text* pText;
public:
    //コンストラクタ
    Timer(GameObject* parent);

    //デストラクタ
    ~Timer();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};