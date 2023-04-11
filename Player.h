#pragma once
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;                            //���f���ԍ�   
    int maxHp_, nowHp_;                     //HP
    bool jumpReady;
    float Gravity_;
    float PlaPosX_, PlaPosY_, PlaPosZ_;     //�v���C���[���W
    double jumpTime;
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
    float GetPlaPosX() { return PlaPosX_ = transform_.position_.x; }
    float GetPlaPosY() { return PlaPosY_ = transform_.position_.y; }
    float GetPlaPosZ() { return PlaPosZ_ = transform_.position_.z; }
};