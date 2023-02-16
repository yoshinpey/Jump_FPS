#pragma once
#include "Engine/GameObject.h"

//HPを管理するクラス
class Gauge : public GameObject
{
    int hpPict_[2];    //画像番号
    int maxHp_, nowHp_;
public:
    //コンストラクタ
    Gauge(GameObject* parent);

    //デストラクタ
    ~Gauge();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //HPセッター
    void SetHp(int maxHp, int nowHp)
    {
        maxHp_ = maxHp;
        nowHp_ = nowHp;
    }
};