#pragma once
#include "Engine/GameObject.h"

//�ߐڍU�����Ǘ�����N���X
class Attack : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Attack(GameObject* parent);

    //�f�X�g���N�^
    ~Attack();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};