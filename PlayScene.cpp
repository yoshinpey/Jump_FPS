#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

#include "Enemy_Fly.h"
#include "PlayScene.h"
#include "Player.h"
#include "Ground.h"
#include "Timer.h"
#include "Gauge.h"
#include "Gun.h"


//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Ground>(this);			//地面登場
	Instantiate<Enemy_Fly>(this);		//敵登場
	Instantiate<Player>(this);			//プレイヤー登場

	//※優先描画
	Instantiate<Timer>(this);			//タイマー登場
	Instantiate<Gauge>(this);			//HPゲージ	

	//背景画像データのロード
	hPict_ = Image::Load("Earth.png");
	assert(hPict_ >= 0);

	//タイマー設定
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(15);
}

//更新
void PlayScene::Update()
{
	TimeProcess();
}

//描画
void PlayScene::Draw()
{
	//背景描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void PlayScene::Release()
{
}

//タイマー
void PlayScene::TimeProcess()
{
	//タイマー起動
	if (Input::IsKeyDown(DIK_T))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->TimeStart();
	}
	//タイマー一時停止
	if (Input::IsKeyDown(DIK_Y))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->TimeStop();
	}
}
