#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"



//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),
    gravity_(-0.1), jumpGauge(50),jumpCool(0), CanJump(false), jumpVel(0.2), jumpTime(0),
    maxHp_(100), nowHp_(100)
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

    //���_�N���X�ǂݍ���
    Instantiate<Aim>(this);

    //�e�L�X�g
    pNum = new Text;
    pNum->Initialize();
}

//�X�V
void Player::Update()
{
    Move();             //����
    CameraPosition();   //���_
    PlayerHitPoint();   //HP

}

//�`��
void Player::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�f�o�b�N�p�e�L�X�g
    pNum->Draw(50, 200, "jumpGauge");
    pNum->Draw(50, 250, jumpGauge);
    pNum->Draw(50, 400, "jumpCool");
    pNum->Draw(50, 450, jumpCool);

    pNum->Draw(1150, 100, "X:");
    pNum->Draw(1200, 100, transform_.position_.x);
    pNum->Draw(1150, 250, "Y:");
    pNum->Draw(1200, 250, transform_.position_.y);
    pNum->Draw(1150, 400, "Z:");
    pNum->Draw(1200, 400, transform_.position_.z);
}

//�J��
void Player::Release()
{
}

//�v���C���[��HP
void Player::PlayerHitPoint()
{
    //HP�Q�[�W�Ăяo��
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
void Player::Move() 
{
    //�ړ�
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    //�G�C�����Ăяo��
    Aim* pAim = (Aim*)FindObject("Aim");

    // Player�N���X��Move�֐����̈ꕔ
    if (Input::IsKey(DIK_W)) {
        fMove.x = pAim->GetAimDirection().x;
        fMove.z = pAim->GetAimDirection().z;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x = pAim->GetAimDirection().z;
        fMove.z = -pAim->GetAimDirection().x;
    }
    if (Input::IsKey(DIK_S)) {
        fMove.x = -pAim->GetAimDirection().x;
        fMove.z = -pAim->GetAimDirection().z;
    }
    if (Input::IsKey(DIK_D)) {
        fMove.x = -pAim->GetAimDirection().z;
        fMove.z = pAim->GetAimDirection().x;   
    }

    
    //�ړ��ʂ����ɒ���
    // �ړ��x�N�g����Aim�R���|�[�l���g�̉�]���ɍ��킹�ĕϊ�
    XMFLOAT3 forward = pAim->GetAimDirection();
    XMVECTOR vMove = XMLoadFloat3(&fMove);
    XMVECTOR rotatedMove = XMVector3Rotate(vMove, XMLoadFloat3(&forward));
    XMStoreFloat3(&fMove, rotatedMove);

    // �ړ��ɔ��f
    transform_.position_.x += fMove.x*0.3;
    transform_.position_.z += fMove.z*0.3;


    //�W�����v�A�N�V����
    Jump();
}

//�W�����v
void Player::Jump()
{
    //�d�� => ���W��0���傫�����ɓ���
    if (transform_.position_.y > 0)
        transform_.position_.y += gravity_;

    //�W�����v�t���O----�Q�[�W��0���傫�����W�����v�\
    if (jumpGauge > 0)
        CanJump = true;

    //�W�����v�\�Ȏ��̏���
    if (CanJump)
    {
        if (Input::IsKey(DIK_SPACE))        //�W�����v�L�[
        {
            if (jumpTime <= 1)              //�������E�ȉ���������
            {
                jumpTime += 0.01;
            }
            jumpGauge--;
            transform_.position_.y += (jumpVel + jumpTime);
        }
        else
        {
            jumpTime = 0;                   //�L�[���͂��Ȃ���΃W�����v�^�C����0�ɂ���
        }
    }

    //�W�����v�s�\�ɂȂ����--�Q�[�W��0�ȉ�
    if (jumpGauge <= 0)
    {
        CanJump = false;                    //�W�����v�s��
        if (jumpCool <= 0)                  //�N�[���^�C����ݒ�
            jumpCool += 30;                 //�Ďg�p�\(�񕜑ҋ@)����
    }

    //�N�[���^�C����0�܂Ō��炷
    if (jumpCool > 0)
    {
        jumpCool--;
    }

    //�W�����v�s�\�Ȏ��̏���--�Q�[�W��Y���W��0�̎��̂݉�
    if (transform_.position_.y <= 0 && jumpCool <= 0)//�N�[���^�C���������Ȃ��Ă��瑝�₷
    {
        if (jumpGauge < 50)//�Q�[�W�̍ő�l�܂�
        {
            jumpGauge++;
        }
    }
}

//���_
void Player::CameraPosition() 
{
    /*�e�X�g�p�̃J����
    XMFLOAT3 camPos{ 0, 10, -20 };
    XMFLOAT3 camTag{ 0, 0, 0 };
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTag);*/
}
