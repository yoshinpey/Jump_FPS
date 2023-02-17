#include "Gravity.h"

//�R���X�g���N�^
Gravity::Gravity(GameObject* parent)
    :GameObject(parent, "Gravity"), gravity_(-0.5)
{
}

//�f�X�g���N�^
Gravity::~Gravity()
{
}

//������
void Gravity::Initialize()
{
}

//�X�V
void Gravity::Update()
{
    //�N�����
    if (Active)
    {
        gravity_ += transform_.position_.y;//��Βl�Q�[������K�v����Q��B�A�A
        gravity_ -= 0.5;
    }
    
}

//�`��
void Gravity::Draw()
{
}

//�J��
void Gravity::Release()
{
}

//�d�͗L��
void Gravity::GravityON()
{
    Active = true;
}

//�d�͖���
void Gravity::GravityOFF()
{
    Active = false;
}
