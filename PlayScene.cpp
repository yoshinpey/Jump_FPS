#include "Engine/SceneManager.h"
#include "Engine/Image.h"

#include "PlayScene.h"
#include "Player.h"

enum
{

};

//コンストラクタ
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	//プレイヤー登場
	Instantiate<Player>(this);
	/*
	//背景画像データのロード
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
	//背景描画
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	*/
}

//開放
void PlayScene::Release()
{
}
