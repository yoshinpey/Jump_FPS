#include "Timer.h"
#include "Engine/Input.h"

static const int FPS = 60;

//�R���X�g���N�^
Timer::Timer(GameObject* parent)
    :GameObject(parent, "Timer"), pNum(nullptr),
    Frame(0), Active(false), drawX(0), drawY(0)
{
}

//�f�X�g���N�^
Timer::~Timer()
{
}

//������
void Timer::Initialize()
{
    pNum = new Text;
    pNum->Initialize();
}

//�X�V
void Timer::Update()
{
    if (Active) 
    {
        if (Frame > 0) 
        {
            Frame--;
        }
    }
}

//�`��
void Timer::Draw()
{
    pNum->SetScale(1.0f);
    pNum->Draw(drawX, drawY, "Time");
    if (Frame % FPS < 10)
        pNum->SetScale((Frame % FPS) * 0.2f + 1.0f);
    else
        pNum->SetScale(1.0f);
    int sec = Frame / FPS;
    pNum->Draw(drawX + 100, drawY, sec);
}

//�J��
void Timer::Release()
{
}

//�^�C�}�[�ݒ�
void Timer::SetLimit(float seconds)
{
    Frame = (int)(seconds * FPS);
}

//�^�C�}�[�J�n
void Timer::TimeStart()
{
    Active = true;
}

//�^�C�}�[�I��
void Timer::TimeStop()
{
    Active = false;
}

//�^�C�}�[�����I��
bool Timer::IsFinished()
{
    return (Frame == 0);
}
