#pragma once
#include "Engine/GameObject.h"

//Enemy_Fly���Ǘ�����N���X
class Enemy_Fly : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Enemy_Fly(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy_Fly();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};