#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
//#include "Gravity.h"
#include "Player.h"
#include "Gauge.h"



//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), 
    Gravity_(-0.1), jumpGauge(120),jumpTime(0), CanJump(false),  jumpVel(0.3),
    PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0), maxHp_(100), nowHp_(100)
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
    Instantiate<Aim>(this);

    pNum = new Text;
    pNum->Initialize();

}

//�X�V
void Player::Update()
{

    PlayerMove();

    CameraPosition();

    PlayerHitPoint();


    //�d�͍͂��W0�ȏ�̎��ɓ���
    if (transform_.position_.y > 0)
    {
        transform_.position_.y += Gravity_;
    }


    //�W�����v�t���O---gauge��0���傫�����W�����v�\
    if (jumpGauge > 0)
    {
        CanJump == true;
    }

    //�W�����v�\�Ȏ��̏���
    if (CanJump=true)
    {
        if (Input::IsKey(DIK_SPACE))
        {
            jumpGauge--;
            jumpTime++; //�o�ߎ��Ԋm�F�p
            transform_.position_.y += jumpVel;
        }
        
    }

    //�W�����v�s�\�ɂȂ����--gauge��0
    if (jumpGauge <= 0)
    {
        CanJump == false;
    }

    //�W�����v�s�\�Ȏ��̏���--gauge��Y��0�̎��ɉ�
    if(transform_.position_.y <= 0 && jumpGauge < 120)
    {
        jumpGauge++;
    }

}

//�`��
void Player::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    pNum->Draw(500, 100, jumpGauge);
    pNum->Draw(500, 300, jumpTime);
    pNum->Draw(500, 500, transform_.position_.x);
    pNum->Draw(800, 500, transform_.position_.y);
    pNum->Draw(1000, 500, transform_.position_.z);
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
    //Camera::SetPosition();
}



