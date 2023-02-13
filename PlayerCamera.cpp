#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"


//�R���X�g���N�^
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1), pNum(nullptr)
{
    moveLength = XMFLOAT3{ 0,0,0 };
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

    //�}�E�X���W�e�L�X�g
    pNum = new Text;
    pNum->Initialize();

    XMFLOAT3 camPos = XMFLOAT3(0, 5, -15);
    Camera::SetPosition(camPos);
}

//�X�V
void PlayerCamera::Update()
{
    //�}�E�X�ړ���
    moveLength = Input::GetMouseMove();

    if (moveLength.x >= 0)
    {
        moveLength.x += transform_.rotate_.y * 0.1;
    }
    else
    {
        moveLength.x -= transform_.rotate_.y * 0.1;
    }


    Camera::SetTarget(moveLength);
    //camPosX += transform_.rotate_.x;
    //camPosX += transform_.rotate_.y;

}

//�`��
void PlayerCamera::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�e�L�X�g
    pNum->Draw(250, 100, moveLength.x);
    pNum->Draw(250, 200, moveLength.y * -1);  //�\�L�����o�I�ɂ킩��₷�����邽�ߏ㉺���]�ɂĕ\��
}

//�J��
void PlayerCamera::Release()
{
}
