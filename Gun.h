#pragma once
#include "Engine/GameObject.h"
//Player�̎q��
//�e���Ǘ�����N���X
class Gun : public GameObject
{
    int hModel_;    //���f���ԍ�
    float Bullet_speed;
public:
    //�R���X�g���N�^
    Gun(GameObject* parent);

    //�f�X�g���N�^
    ~Gun();
    
    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};