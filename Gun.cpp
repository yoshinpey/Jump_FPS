#include "Engine/Model.h"

#include "Gun.h"


//�R���X�g���N�^
Gun::Gun(GameObject* parent)
    :GameObject(parent, "Gun"), hModel_(-1)
{
}

//�f�X�g���N�^
Gun::~Gun()
{
}

//������
void Gun::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("�t�@�C����");
    assert(hModel_ >= 0);
}

//�X�V
void Gun::Update()
{
}

//�`��
void Gun::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Gun::Release()
{
}