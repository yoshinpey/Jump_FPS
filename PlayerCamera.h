#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class PlayerCamera : public GameObject
{
    int hModel_;                            //モデル番号
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //プレイヤー位置
    XMFLOAT3 fPoint;                        //マウスの移動
    XMFLOAT3 camPos, camTarget;             //カメラ 位置,焦点
    XMVECTOR vMove;                         //1フレームの移動ベクトル
    XMVECTOR vPos;                          //1フレームの位置ベクトル
    Text* pNum;                             //テキスト
public:
    //コンストラクタ
    PlayerCamera(GameObject* parent);

    //デストラクタ
    ~PlayerCamera();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //カメラ回転
    /*
    XMVECTOR GetCamRotate()
    {
        return vMove;
    };
    */
};