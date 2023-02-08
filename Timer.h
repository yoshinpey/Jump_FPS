#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

static const int FPS = 60;

//Timer管理するクラス
class Timer : public GameObject
{
    int timer;
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

    void Start(float seconds);

    bool IaFinished();


};