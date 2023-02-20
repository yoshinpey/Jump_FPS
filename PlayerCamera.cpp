#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"
#include "Gun.h"


//�R���X�g���N�^
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1),
    pNum(nullptr), PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0),
    camPos{ 0,0,0 }, camTarget{ 0,0,0 }, fPoint{ 0,0,0 },
    vMove{ 0.0f, 0.0f, 0.0f, 0.0f}
{
}

//�f�X�g���N�^
PlayerCamera::~PlayerCamera()
{
}

//������
void PlayerCamera::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Character/PlayerCamera.fbx");
    assert(hModel_ >= 0);
    transform_.position_.x = 0;
    transform_.position_.y = 2;
    transform_.position_.z = 0;

    //�}�E�X���W�e�L�X�g
    pNum = new Text;
    pNum->Initialize();

    //�e�̓J�����ɂ�
    Instantiate<Gun>(this);

    Input::SetMousePosition(300, 250);//�}�E�X�����ʒu(��ʒ���)
}

//�X�V
void PlayerCamera::Update()
{
    
    //�}�E�X�ړ���
    fPoint = Input::GetMouseMove();

    //�v���C���[���W�擾
    Player* pPlayer = (Player*)FindObject("Player");
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();

    //�}�E�X�ʒu�ۑ��p�ϐ�
    float Px=0,Py=0;

    //�ړ��ʂ����Z
    Px += fPoint.x;
    Py += fPoint.y;
    //��]�ړ��ɔ��f
    transform_.rotate_.y += Px *0.05;
    transform_.rotate_.x += Py *0.05;

    //���ݒn���x�N�g���ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //�J�����̉�]���s���
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vMove = { 0.0f, 0.0f, 1.0f};
    //���_���Œ�
    vMove = XMVector3TransformCoord(vMove, mRotY*mRotX);

    //�J�����̈ʒu(�ړ�)
    camPos = transform_.position_;   //�ڐ���������
    Camera::SetPosition(camPos);

    //�J�����œ_
    XMStoreFloat3(&camTarget, vPos + vMove);
    Camera::SetTarget(camTarget);

    //XMFLOAT3 GunTop = Model::GetBonePosition(hModel_, "Top");
    //Camera::SetTarget(GunTop);

}

//�`��
void PlayerCamera::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�f�o�b�N�p�e�L�X�g
    pNum->Draw(650, 400, "+");
    pNum->Draw(1100, 100, "X:   ");
    pNum->Draw(1150, 100,  fPoint.x);
    pNum->Draw(1100, 200, "Y:   ");
    pNum->Draw(1150, 200, fPoint.y * -1);//�\�L�����o�I�ɂ킩��₷�����邽�ߏ㉺���]�\��
}

//�J��
void PlayerCamera::Release()
{
}
