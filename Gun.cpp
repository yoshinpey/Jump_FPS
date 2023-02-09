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
    hModel_ = Model::Load("Entity/Rifle_mini.fbx");
    assert(hModel_ >= 0);

    transform_.position_.y = 0.72;
    transform_.position_.x = 0.25;
    transform_.position_.z = 1.5;
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