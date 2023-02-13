#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"


//�R���X�g���N�^
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1), pNum(nullptr), camPosX(0), camPosY(0)
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
    transform_.position_.x = 0;
    transform_.position_.y = 5;
    transform_.position_.z =-10;

    //�}�E�X���W�e�L�X�g
    pNum = new Text;
    pNum->Initialize();


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

    //�Ⴄ�B�B�B�B�B�B�B�B�B�B�B�B�B�B
    //camPosX = Player::GetPlayerPositionX(camPosX);
    XMFLOAT3 camPos = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z);
    Camera::SetPosition(camPos);
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
