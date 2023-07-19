#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Score���Ǘ�����N���X
class Score : public GameObject
{
    Text* pText;    //�e�L�X�g
    int score_;     //�X�R�A
    bool Active;    //�N�����Ă��邩�ǂ���
    float drawX;    //�`��ʒu(���E)
    float drawY;    //�`�捂��

public:
    Score(GameObject* parent);      //�R���X�g���N�^
    ~Score();                       //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��

    int ScoreAdd();

    //�^�C�}�[�ݒ�
    void SetLimit(float seconds);

    //�^�C�}�[�J�n
    void Start();

    //�^�C�}�[�I��
    void Stop();

    //�^�C�}�[�����I��
    bool IsFinished();
};