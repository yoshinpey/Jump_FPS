#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class PlayerCamera : public GameObject
{
    int hModel_;            //モデル番号
    XMFLOAT3 fPoint, fPoint2, fMove;
    float PlaPosX_, PlaPosY_, PlaPosZ_;
    XMFLOAT3 camPos;
    Text* pNum;
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

};