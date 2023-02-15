#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"
#include "Gun.h"


//�R���X�g���N�^
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1), pNum(nullptr)
{
    XMFLOAT3 fMove = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 fPoint = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 camPos = XMFLOAT3{ 0,0,0 };
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
    transform_.position_.y = 3;
    transform_.position_.z = -1;

    //�}�E�X���W�e�L�X�g
    pNum = new Text;
    pNum->Initialize();

    //�e�̓J�����̌��������֓�����
    Instantiate<Gun>(this);
}

//�X�V
void PlayerCamera::Update()
{
    //�}�E�X�ړ���
    fPoint = Input::GetMouseMove();

    if (length != 0)
    {
        XMVECTOR vFront = { 0,0,1,0 };
        vMove = XMVector3Normalize(vMove);

        //����
        XMVECTOR vDot = XMVector3Dot(vFront, vMove);
        float dot = XMVectorGetX(vDot);
        float angle = acos(dot);

        //�O��
        XMVECTOR vCross = XMVector3Cross(vFront, vMove);
        if (XMVectorGetY(vCross) < 0)
        {
            angle *= -1;
        }

        //�f�O���[�ɕϊ��@
        transform_.rotate_.y = XMConvertToDegrees(angle);
        //���Ȃ݂�  �@XMConvertToRadians()      <--���W�A���ɕϊ�180�������W�A��
    }
}

//�`��
void PlayerCamera::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�e�L�X�g
    pNum->Draw(250, 100, fPoint.x);
    pNum->Draw(250, 200, fPoint.y * -1);  //�\�L�����o�I�ɂ킩��₷�����邽�ߏ㉺���]�ɂĕ\��
}

//�J��
void PlayerCamera::Release()
{
}
