#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
//#include "Gravity.h"
#include "Player.h"
#include "Gauge.h"



//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), Gravity_(-0.1), 
    PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0), maxHp_(100), nowHp_(100),
    jumpReady(false)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/Human_only.fbx");
    assert(hModel_ >= 0);

    //�J����
    Instantiate<PlayerCamera>(this);

}

//�X�V
void Player::Update()
{

    PlayerMove();

    CameraPosition();

    PlayerHitPoint();

    //Gravity* pGravity = (Gravity*)FindObject("Gravity");
    //Gravity_ = pGravity->SetGravity(transform_.position_.y);

    float velocity = 1.0f;
    if (transform_.position_.y > 0)
    {
        jumpReady = false;
        transform_.position_.y += Gravity_;//�d��
    }
    else
    {
        jumpReady = true;
    }

    //�W�����v�́i�㏸���x�j
    if (jumpReady == true)//�W�����v�\
    {
        if (Input::IsKeyDown(DIK_SPACE))//�����ꂽ��W�����v
        {
            if (velocity < 9)//�W�����v��
            {
                velocity += 3.0f;
            }

            transform_.position_.y += velocity;
            velocity += Gravity_;
        }
    }
}

//�`��
void Player::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}

//�v���C���[��HP
void Player::PlayerHitPoint()
{
    //HP
    Gauge* pGauge = (Gauge*)FindObject("Gauge");
    pGauge->SetHp(maxHp_, nowHp_);

    //�G���[�ׂ�
    if (Input::IsKeyDown(DIK_M))
    {
        nowHp_ += 20;
        if (nowHp_ > maxHp_)
        {
            nowHp_ = maxHp_;
        }
    }
    if (Input::IsKeyDown(DIK_N))
    {
        nowHp_ -= 20;
        if (nowHp_ < 0)
        {
            nowHp_ = 0;
        }
    }
}

//�v���C���[�̈ړ�
void Player::PlayerMove() 
{
    //�ړ�
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    if (Input::IsKey(DIK_W)){
        fMove.z = 1.0f;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x = -1.0f;
    }
    if (Input::IsKey(DIK_S)){
        fMove.z = -1.0f;
    }
    if (Input::IsKey(DIK_D)){
        fMove.x = 1.0f;
    }

    //�ړ��ʂ����ɒ���
    XMVECTOR vMove;
    vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    vMove *= 0.1f;
    XMStoreFloat3(&fMove, vMove);

    //�ړ��ɔ��f
    transform_.position_.x += fMove.x;
    transform_.position_.z += fMove.z;
}

//���_
void Player::CameraPosition() 
{
    //test
}



