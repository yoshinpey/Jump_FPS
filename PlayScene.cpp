#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

#include "Enemy_Fly.h"
#include "PlayScene.h"
#include "Player.h"
#include "Ground.h"
#include "Timer.h"
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
	Instantiate<Timer>(this);			//タイマー登場
	Instantiate<Player>(this);			//プレイヤー登場
	Instantiate<Enemy_Fly>(this);

	//タイマー設定
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(15);
	/*
	//背景画像データのロード
	hPict_ = Image::Load("ファイル名");
	assert(hPict_ >= 0);
	*/
}

//更新
void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_Y))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->TimeStart();
	}

	if (Input::IsKeyDown(DIK_H))
	{
		Timer* t = (Timer*)FindObject("Timer");
		t->TimeStop();
	}
}

//描画
void PlayScene::Draw()
{
	/*
	//背景描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	*/
}

//開放
void PlayScene::Release()
{
}
