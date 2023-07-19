#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Scoreを管理するクラス
class Score : public GameObject
{
    Text* pText;    //テキスト
    int score_;     //スコア
    bool Active;    //起動しているかどうか
    float drawX;    //描画位置(左右)
    float drawY;    //描画高さ

public:
    Score(GameObject* parent);      //コンストラクタ
    ~Score();                       //デストラクタ
    void Initialize() override;     //初期化
    void Update() override;         //更新
    void Draw() override;           //描画
    void Release() override;        //開放

    int ScoreAdd();

    //タイマー設定
    void SetLimit(float seconds);

    //タイマー開始
    void Start();

    //タイマー終了
    void Stop();

    //タイマー処理終了
    bool IsFinished();
};