#pragma once
#include "Engine/GameObject.h"

//�n��G���Ǘ�����N���X
class Enemy_Ground : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Enemy_Ground(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy_Ground();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};