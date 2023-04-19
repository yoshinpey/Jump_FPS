#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Player.h"
#include "Gun.h"


//コンストラクタ
Aim::Aim(GameObject* parent)
    :GameObject(parent, "Aim"), pNum(nullptr), 
    PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0),
    camPos{ 0,0,0 }, camTarget{ 0,0,0 }, fPoint{ 0,0,0 },
    vPos{ 0,0,0,0 },  vMove{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

//デストラクタ
Aim::~Aim()
{
}

//初期化
void Aim::Initialize()
{
    transform_.position_.y = 2;

    //マウス座標テキスト
    pNum = new Text;
    pNum->Initialize();

    //銃はカメラにつく
    Instantiate<Gun>(this);

    Input::SetMousePosition(300, 250);//マウス初期位置(画面中央)
}

//更新
void Aim::Update()
{
    

}

//描画
void Aim::Draw()
{

    //デバック用テキスト
    pNum->Draw(650, 400, "+");
    pNum->Draw(1100, 100, "X:   ");
    pNum->Draw(1150, 100,  fPoint.x);
    pNum->Draw(1100, 200, "Y:   ");
    pNum->Draw(1150, 200, fPoint.y * -1);//表記を視覚的にわかりやすくするため上下反転表示
}

//開放
void Aim::Release()
{
}
