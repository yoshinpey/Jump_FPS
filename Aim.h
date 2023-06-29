#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class Aim : public GameObject
{
    XMFLOAT3 plaPos_;                       //�v���C���[�ʒu
    XMFLOAT3 camPos, camTarget;             //�J���� �ʒu,�œ_
    Text* pNum;                             //�e�L�X�g
    XMFLOAT3 aimDirection_;                 //���݂̎��_�Ɋ�Â����i�s�����x�N�g��
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

    //�i�s�����x�N�g����Aim�����擾
    XMFLOAT3 GetAimDirection(){ return aimDirection_; }
};