#pragma once
#include "Engine/GameObject.h"

//Player���Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�
    int camType_;
public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�v���C���[�ړ�
    void PlayerMove();
};