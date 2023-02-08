#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//タイマー管理するクラス
class Timer : public GameObject
{
    bool Active;        //起動しているかどうか
    int Frame;          //一秒間に何回更新されるか
    Text* pNum;         //秒数テキスト
    float drawX;        //描画位置(左右)
    float drawY;        //描画高さ

public:
    //コンストラクタ
    Timer(GameObject* parent);
    //デストラクタ
    ~Timer();
    //初期化
    void Initialize() override;
    //更新
    void Update() override;
    //描画
    void Draw() override;
    //開放
    void Release() override;

    //タイマー設定
    void SetLimit(float seconds);

    //タイマー開始
    void TimeStart();

    //タイマー終了
    void TimeStop();

    //タイマー処理終了
    bool IsFinished();
};