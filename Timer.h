#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Timer�Ǘ�����N���X
class Timer : public GameObject
{
    bool Active;
    int Frame;
    Text* pNum;
    float drawX;
    float drawY;

public:
    //�R���X�g���N�^
    Timer(GameObject* parent);
    //�f�X�g���N�^
    ~Timer();
    //������
    void Initialize() override;
    //�X�V
    void Update() override;
    //�`��
    void Draw() override;
    //�J��
    void Release() override;

    //�^�C�}�[�ݒ�
    void SetLimit(float seconds);

    //�^�C�}�[�J�n
    void TimeStart();

    //�^�C�}�[�I��
    void TimeStop();

    //�^�C�}�[�����I��
    bool IsFinished();
};