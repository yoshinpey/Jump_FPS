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

    //�|�C���g�Z�b�g
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMove = { 0.0f, 0.0f, 0.3f, 0.0f, };//����0.3�ړ�
    

    XMVECTOR vPoint = XMLoadFloat3(&fPoint);
    XMVECTOR vPoint2 = XMLoadFloat3(&fPoint2);
    XMVECTOR vMove = vPoint - vPoint2;

    //vMove = XMVector3Normalize(vMove);
    //vMove *= 0.3;

    Camera::SetPosition(transform_.position_);

    XMFLOAT3 camTarget;
    XMStoreFloat3(&camTarget, vPoint + vMove);
    Camera::SetTarget(camTarget);

    //�J�����𓪂Ɉʒu�ɃZ�b�g
    camPos = transform_.position_;
    
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
