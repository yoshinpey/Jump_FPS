#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class PlayerCamera : public GameObject
{
    int hModel_;                            //���f���ԍ�
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //�v���C���[�ʒu
    XMFLOAT3 fPoint;                        //�}�E�X�̈ړ�
    XMFLOAT3 camPos, camTarget;             //�J���� �ʒu,�œ_
    XMVECTOR vMove;                         //1�t���[���̈ړ��x�N�g��
    XMVECTOR vPos;                          //1�t���[���̈ʒu�x�N�g��
    Text* pNum;                             //�e�L�X�g
public:
    //�R���X�g���N�^
    PlayerCamera(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerCamera();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�J������]
    /*
    XMVECTOR GetCamRotate()
    {
        return vMove;
    };
    */
};