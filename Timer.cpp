#include "Timer.h"

//�R���X�g���N�^
Timer::Timer(GameObject* parent)
    :GameObject(parent, "Timer"), pText(nullptr)
{
}

//�f�X�g���N�^
Timer::~Timer()
{
}

//������
void Timer::Initialize()
{
    pText = new Text;
    pText->Initialize();
}

//�X�V
void Timer::Update()
{
}

//�`��
void Timer::Draw()
{
    //pText->Draw(30, 30, "Hello");
}

//�J��
void Timer::Release()
{
}