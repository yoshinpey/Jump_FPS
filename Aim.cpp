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
   
    //マウス移動量
    fPoint = Input::GetMouseMove();

    //プレイヤー座標取得
    Player* pPlayer = (Player*)FindObject("Player");
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();

    //マウス位置保存用変数
    float Px=0,Py=0;

    //移動量を加算
    Px += fPoint.x;
    Py += fPoint.y;
    //回転移動に反映
    transform_.rotate_.y += Px *0.05;
    transform_.rotate_.x += Py *0.05;

    //現在地をベクトルに変換
    vPos = XMLoadFloat3(&transform_.position_);

    //カメラの回転
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //方向
    vMove = { 0, 0, 1, 0};
    //視点を固定
    vMove = XMVector3TransformCoord(vMove, mRotY*mRotX);

    Camera::SetPosition(camPos);
    //カメラの位置(移動)
    camPos.x = PlaPosX_;   //
    camPos.y = PlaPosY_+2; //目線高さ
    camPos.z = PlaPosZ_;   //

    //カメラ焦点
    XMStoreFloat3(&camTarget, vPos + vMove);
    Camera::SetTarget(camTarget);

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
