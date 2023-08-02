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
    hModel_ = Model::Load("Character/Mob_Robot.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = 1;
    transform_.position_.z = 10;
    transform_.rotate_.y = 180;

    //�A�j���[�V����
    Model::SetAnimFrame(hModel_, 0, 120, 1.00);

}

//�X�V
void Enemy_Fly::Update()
{
    transform_.rotate_.y += 0.5;    


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