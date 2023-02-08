#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//�^�C�}�[�Ǘ�����N���X
class Timer : public GameObject
{
    bool Active;        //�N�����Ă��邩�ǂ���
    int Frame;          //��b�Ԃɉ���X�V����邩
    Text* pNum;         //�b���e�L�X�g
    float drawX;        //�`��ʒu(���E)
    float drawY;        //�`�捂��

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