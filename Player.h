#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;            //���f���ԍ�
    double camPosX;        
    double camPosY;        
    Text* pNum;             
    XMFLOAT3 moveLength;    
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