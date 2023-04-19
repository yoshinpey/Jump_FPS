#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Aim : public GameObject
{
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //プレイヤー位置
    XMFLOAT3 fPoint;                        //マウスの移動
    XMFLOAT3 camPos, camTarget;             //カメラ 位置,焦点
    XMVECTOR vPos, vMove;                    //1フレームの位置,移動ベクトル
    Text* pNum;                             //テキスト
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

};