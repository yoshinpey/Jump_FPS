#include "Score.h"

//�R���X�g���N�^
Score::Score(GameObject* parent)
    :GameObject(parent, "Score"), pText(nullptr), 
    Active(false), drawX(10), drawY(20)
{
}

//�f�X�g���N�^
Score::~Score()
{
}

//������
void Score::Initialize()
{
    pText = new Text;
    pText->Initialize();
}

//�X�V
void Score::Update()
{
}

//�`��
void Score::Draw()
{
    //pText->Draw(30, 30, "Hello");
}

//�J��
void Score::Release()
{
}