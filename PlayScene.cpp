#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "PlayScene.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject * parent)
	: GameObject(parent, "PlayScene"), hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("�t�@�C����");
	assert(hPict_ >= 0);
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void PlayScene::Release()
{
}
