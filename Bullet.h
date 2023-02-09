#pragma once
#include "Engine/GameObject.h"
//銃の子供
//銃弾を管理するクラス
class Bullet : public GameObject
{
    int hModel_;            //モデル番号    
    int BulletKill_;        

    XMFLOAT3 move_;         

public:
    //コンストラクタ
    Bullet(GameObject* parent);

    //デストラクタ
    ~Bullet();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //弾の位置設定用
    void SetMove(XMFLOAT3 move) { move_ = move; }
};