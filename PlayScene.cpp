#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

#include "Enemy_Fly.h"
#include "PlayScene.h"
#include "Player.h"
#include "Ground.h"
#include "Timer.h"
#include "Gun.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	
	Instantiate<Ground>(this);			//�n�ʓo��
	Instantiate<Timer>(this);			//�^�C�}�[�o��
	Instantiate<Player>(this);			//�v���C���[�o��
	Instantiate<Enemy_Fly>(this);

	//�^�C�}�[�ݒ�
	Timer* t = (Timer*)FindObject("Timer");
	t->SetLimit(15);
	/*
	//�w�i�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("�t�@�C����");
	assert(hPict_ >= 0);
	*/
}

//�X�V
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

//�`��
void PlayScene::Draw()
{
	/*
	//�w�i�`��
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	*/
}

//�J��
void PlayScene::Release()
{
}
