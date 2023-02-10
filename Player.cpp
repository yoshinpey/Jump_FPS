#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Player.h"
#include "Gun.h"


//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), pNum(nullptr)
{
    movelen1 = XMFLOAT3{ 0,0,0 };
    movelen2 = XMFLOAT3{ 0,0,0 };
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

    //�e��o�ꂳ����
    Instantiate<Gun>(this);

    pNum = new Text;
    pNum->Initialize();
}

//�X�V
void Player::Update()
{
    movelen1 = Input::GetMouseMove();

    PlayerMove();

    CameraPosition();


}

//�`��
void Player::Draw()
{
    pNum->Draw(250, 100, movelen1.x);
    pNum->Draw(250, 200, movelen1.y);

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


}

//�J��
void Player::Release()
{
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

    XMVECTOR vMove;
    vMove = XMLoadFloat3(&fMove);
    vMove = XMVector3Normalize(vMove);
    vMove *= 0.1f;
    XMStoreFloat3(&fMove, vMove);

    transform_.position_.x += fMove.x;
    transform_.position_.z += fMove.z;

    //�����ύX  
    XMVECTOR vLength = XMVector3Length(vMove);
    float length = XMVectorGetX(vLength);
    //�x�N�g��
    XMVECTOR vFront = { 0,0,1,0 };
    vMove = XMVector3Normalize(vMove);

    //�ړ����͂��Ȃ��Ƃ��͌������Œ�
    if (length != 0)
    {
        //����
        XMVECTOR vDot = XMVector3Dot(vFront, vMove);
        float dot = XMVectorGetX(vDot);
        float angle = acos(dot);
        //�O��
        XMVECTOR vCross = XMVector3Cross(vFront, vMove);
        if (XMVectorGetY(vCross) < 0){
            angle *= -1;
        }
        //�f�O���[�ɕϊ��@
        transform_.rotate_.y = XMConvertToDegrees(angle);
    }
}

void Player::CameraPosition() 
{
    //�Ƃ肠�����̃J����
    XMFLOAT3 camPos = XMFLOAT3(0, 5, -15);
    Camera::SetPosition(camPos);
    
    //�}�E�X�ɘA�����鎋�_����肽���I�I

}

void Player::GetPlayerPosition()
{
}
