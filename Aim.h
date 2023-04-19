#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class Aim : public GameObject
{
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //�v���C���[�ʒu
    XMFLOAT3 fPoint;                        //�}�E�X�̈ړ�
    XMFLOAT3 camPos, camTarget;             //�J���� �ʒu,�œ_
    XMVECTOR vPos, vMove;                    //1�t���[���̈ʒu,�ړ��x�N�g��
    Text* pNum;                             //�e�L�X�g
public:
    //�R���X�g���N�^
    Aim(GameObject* parent);

    //�f�X�g���N�^
    ~Aim();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};