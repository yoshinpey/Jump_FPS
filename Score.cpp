#include "Score.h"

//コンストラクタ
Score::Score(GameObject* parent)
    :GameObject(parent, "Score"), pText(nullptr), 
    Active(false), drawX(10), drawY(20)
{
}

//デストラクタ
Score::~Score()
{
}

//初期化
void Score::Initialize()
{
    pText = new Text;
    pText->Initialize();
}

//更新
void Score::Update()
{
}

//描画
void Score::Draw()
{
    //pText->Draw(30, 30, "Hello");
}

//開放
void Score::Release()
{
}