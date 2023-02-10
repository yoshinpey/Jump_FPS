#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//主人公を管理するクラス
class Player : public GameObject
{
    int hModel_;            //モデル番号
    double camPosX;        
    double camPosY;        
    Text* pNum;             
    XMFLOAT3 moveLength;    
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //プレイヤー移動
    void PlayerMove();

    //カメラ
    void CameraPosition();

    //get
    void GetPlayerPosition();
};