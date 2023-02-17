#pragma once
#include "Engine/GameObject.h"

//  �d�͂��Ǘ�����N���X
class Gravity : public GameObject
{
    bool Active;
    float gravity_;
public:
    //�R���X�g���N�^
    Gravity(GameObject* parent);

    //�f�X�g���N�^
    ~Gravity();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�d�͗L��
    void GravityON();

    //�d�͖���
    void GravityOFF();
};