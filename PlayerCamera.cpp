#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "PlayerCamera.h"
#include "Player.h"
#include "Gun.h"


//�R���X�g���N�^
PlayerCamera::PlayerCamera(GameObject* parent)
    :GameObject(parent, "PlayerCamera"), hModel_(-1), pNum(nullptr), PlaPosX_(0), PlaPosY_(0), PlaPosZ_(0)
{
    XMFLOAT3 fMove = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 fPoint = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 camPos = XMFLOAT3{ 0,0,0 };
    XMFLOAT3 plaPos_ = XMFLOAT3{ 0,0,0 };
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
}

//�X�V
void PlayerCamera::Update()
{
    //�}�E�X�ړ���
    fPoint = Input::GetMouseMove();

    Player* pPlayer = (Player*)FindObject("Player");
    PlaPosX_ = pPlayer->GetPlaPosX();
    PlaPosY_ = pPlayer->GetPlaPosY();
    PlaPosZ_ = pPlayer->GetPlaPosZ();


}

//�`��
void PlayerCamera::Draw()
{
    //���f��
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //�f�o�b�N�p�e�L�X�g
    pNum->Draw(250, 100, fPoint.x);
    pNum->Draw(250, 200, fPoint.y * -1);  //�\�L�����o�I�ɂ킩��₷�����邽�ߏ㉺���]�\��
}

//�J��
void PlayerCamera::Release()
{
}
