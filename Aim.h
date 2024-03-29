#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//視点を管理するクラス
class Aim : public GameObject
{
    float screenWidth_, screenHeight_;
    XMFLOAT3 plaPos_;                       //プレイヤー位置
    XMFLOAT3 camPos_, camTarget_;             //カメラ 位置,焦点
    Text* pNum_;                             //テキスト
    XMFLOAT3 aimDirection_;                 //現在の視点に基づいた進行方向ベクトル
public:
    Aim(GameObject* parent);        //コンストラクタ
    ~Aim();                         //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    //進行方向ベクトルのAim情報を取得
    XMFLOAT3 GetAimDirection(){ return aimDirection_; }
};