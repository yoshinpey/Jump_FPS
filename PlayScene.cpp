#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "PlayScene.h"
#include "Player.h"


//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Player>(this);
	/*
	//画像データのロード
	hPict_ = Image::Load("ファイル名");
	assert(hPict_ >= 0);
	*/
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
	/*
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//開放
void PlayScene::Release()
{
}
