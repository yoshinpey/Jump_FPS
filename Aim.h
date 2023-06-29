#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Aim : public GameObject
{
    XMFLOAT3 plaPos_;                       //プレイヤー位置
    XMFLOAT3 camPos, camTarget;             //カメラ 位置,焦点
    Text* pNum;                             //テキスト
    XMFLOAT3 aimDirection_;                 //現在の視点に基づいた進行方向ベクトル
public:
    //コンストラクタ
    Aim(GameObject* parent);

    //デストラクタ
    ~Aim();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //進行方向ベクトルのAim情報を取得
    XMFLOAT3 GetAimDirection(){ return aimDirection_; }
};