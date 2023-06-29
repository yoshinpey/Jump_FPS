#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Scoreを管理するクラス
class Score : public GameObject
{
    Text* pText;    //テキスト

public:
    Score(GameObject* parent);      //コンストラクタ
    ~Score();                       //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放


};