#pragma once
#include "Engine/GameObject.h"

//Crystal���Ǘ�����N���X
class Crystal : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Crystal(GameObject* parent);

    //�f�X�g���N�^
    ~Crystal();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};