#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;                            //���f���ԍ�   
    int maxHp_, nowHp_;                     //HP 
    bool CanJump;                           //�W�����v�\��
    float gravity_, jumpGauge, jumpCool,    //�d�́A�W�����v�Q�[�W�A���`���[�W����
          jumpVel, jumpTime;                //�W�����v�́A�����x�ω��p�^�C�}�[
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //�v���C���[���W
   
    Text* pNum;
public:
    Player(GameObject* parent);     //�R���X�g���N�^
    ~Player();                      //�f�X�g���N�^
    void Initialize() override;     //������
    void Update() override;         //�X�V
    void Draw() override;           //�`��
    void Release() override;        //�J��
    
    //�A�N�V����
    void Move();                    //�v���C���[�̈ړ�
    void Jump();                    //�W�����v
    void PlayerHitPoint();          //�̗�
    void CameraPosition();          //���_

    //�v���C���[���W�̃Q�b�^�[
    float GetPlaPosX() { return transform_.position_.x; }
    float GetPlaPosY() { return transform_.position_.y; }
    float GetPlaPosZ() { return transform_.position_.z; }
};