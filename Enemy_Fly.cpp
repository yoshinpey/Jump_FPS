#include "Engine/Model.h"

#include "Enemy_Fly.h"


//�R���X�g���N�^
Enemy_Fly::Enemy_Fly(GameObject* parent)
    :GameObject(parent, "Enemy_Fly"), hModel_(-1)
{
}

//�f�X�g���N�^
Enemy_Fly::~Enemy_Fly()
{
}

//������
void Enemy_Fly::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);
}

//�X�V
void Enemy_Fly::Update()
{
}

//�`��
void Enemy_Fly::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Enemy_Fly::Release()
{
}