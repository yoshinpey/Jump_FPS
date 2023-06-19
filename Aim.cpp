#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Player.h"
#include "Gun.h"


//�R���X�g���N�^
Aim::Aim(GameObject* parent)
    :GameObject(parent, "Aim"), pNum(nullptr),
    PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0),
    camPos{ 0,0,0 }, camTarget{ 0,0,0 }, fPoint{ 0,0,0 },
    vPos{ 0,0,0,0 }, vMove{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

//�f�X�g���N�^
Aim::~Aim()
{
}

//������
void Aim::Initialize()
{
    transform_.position_.y = 2;

    //�}�E�X���W�e�L�X�g
    pNum = new Text;
    pNum->Initialize();

    //�e�̓J�����ɂ�
    Instantiate<Gun>(this);

   
}

//�X�V
void Aim::Update()
{ 
    Input::SetMousePosition(800/2, 600/2);//�}�E�X�����ʒu(��ʒ���)
    //�}�E�X�ړ���
    XMFLOAT3 mouseMove = Input::GetMouseMove(); // �}�E�X�̈ړ��ʂ��擾

    //�ړ��ʂ����Z
    transform_.rotate_.y += static_cast<float>(mouseMove.x) * 0.05f; // �������̉�]
    transform_.rotate_.x += static_cast<float>(mouseMove.y) * 0.05f; // �c�����̉�]

    //�v���C���[���W�擾
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();

    //�v���C���[�L�����N�^�[�̈ʒu���J�����̈ʒu�Ƃ���
    camPos.x = PlaPosX_;
    camPos.y = PlaPosY_ + 2; //�ڐ�����
    camPos.z = PlaPosZ_;

    //�J�����̉�]
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //�J�����̈ʒu�Ɖ�]������
    XMMATRIX mView = mRotX * mRotY;

    //�J�����̈ʒu�Əœ_���擾
    XMVECTOR camPosVector = XMLoadFloat3(&camPos);
    XMVECTOR camTarget = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    camTarget = XMVector3TransformCoord(camTarget, mView);
    camTarget = XMVectorAdd(camPosVector, camTarget);

    //�J�����̈ʒu�Əœ_��ݒ�
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, camTarget);
    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);
}


//�`��
void Aim::Draw()
{

    //�f�o�b�N�p�e�L�X�g
    pNum->Draw(650, 400, "+");
    pNum->Draw(1100, 100, "X:   ");
    pNum->Draw(1150, 100, fPoint.x);
    pNum->Draw(1100, 200, "Y:   ");
    pNum->Draw(1150, 200, fPoint.y * -1);//�\�L�����o�I�ɂ킩��₷�����邽�ߏ㉺���]�\��
}

//�J��
void Aim::Release()
{
}
