#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;                            //���f���ԍ�   
    int TheZERO;                            //���Ӗ��ȕϐ��B�[���B
    int maxHp_, nowHp_;                     //HP 
    bool CanJump;                           //�W�����v�\
    float Gravity_, jumpGauge, jumpCool,    //�d�́A�W�����v�Q�[�W�A���`���[�W����
          jumpVel, jumpTime;                //�W�����v�́A�����x�ω��p�^�C�}�[
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //�v���C���[���W
   
    Text* pNum;
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

    //�v���C���[HP
    void PlayerHitPoint();

    //�J����
    void CameraPosition();

    //�W�����v


    //�v���C���[���W�̃Q�b�^�[
    float GetPlaPosX() { return transform_.position_.x; }
    float GetPlaPosY() { return transform_.position_.y; }
    float GetPlaPosZ() { return transform_.position_.z; }
};