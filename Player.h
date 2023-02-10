#pragma once
#include "Engine/GameObject.h"

//��l�����Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�
    XMVECTOR camPos;
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

    //�J����
    void CameraPosition();

    //get
    void GetPlayerPosition();
};