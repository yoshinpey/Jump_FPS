#pragma once
#include "Engine/GameObject.h"

//Bomb���Ǘ�����N���X
class Bomb : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Bomb(GameObject* parent);

    //�f�X�g���N�^
    ~Bomb();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};