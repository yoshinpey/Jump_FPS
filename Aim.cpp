#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

#include "Aim.h"
#include "Player.h"
#include "Gun.h"


//�R���X�g���N�^
Aim::Aim(GameObject* parent)
    :GameObject(parent, "Aim"), pNum(nullptr),
    plaPos_{0,0,0},camPos{ 0,0,0 }, camTarget{ 0,0,0 }
{
}

//�f�X�g���N�^
Aim::~Aim()
{
}

//������
void Aim::Initialize()
{
    //�G�C���N���X�̌Ăяo���ʒu
    transform_.position_.y = 2;

    //�}�E�X���W�e�L�X�g
    pNum = new Text;
    pNum->Initialize();

    //�e�̓J�����ɂ�
    Instantiate<Gun>(this);

    //�}�E�X�����ʒu(��/2, ����/2)
    Input::SetMousePosition(800/2, 600/2);
}

//�X�V
void Aim::Update()
{ 
    /*/////////////////////////////////////////���̂��߂ɐ��w��׋��������܂����B
    ----------------------------
    //���߂̃}�E�X�ʒu���W���擾
    XMFLOAT3 firstMousePos_ = Input::GetMousePosition();
    ------------------------------

    //���݂̃}�E�X�ʒu���W���擾
    XMFLOAT3 mousePos_ = Input::GetMousePosition();

    //�ړ��x�N�g�� �� �����ʒu - ���ݒn
    float deltaX = firstMousePos_.x - mousePos_.x;
    float deltaY = firstMousePos_.y - mousePos_.y;

    //�������Z�o
    direction_ = -(float)atan2(deltaX, deltaY);
    /////////////////////////////////////////////////*/
    
    //////////////////////////////////////���邢�́A�A�A�A�A�A
    //�}�E�X�̈ړ��ʂ��擾
    XMFLOAT3 mouseMove = Input::GetMouseMove();
    
    //�ړ��x�N�g���̒������v�Z------3�����̒藝------
    float moveLength = sqrtf(mouseMove.x * mouseMove.x + mouseMove.y * mouseMove.y);

    //�����x�N�g�����v�Z-----���K��-----
    XMFLOAT3 fDirection{};
    fDirection.x = mouseMove.x / moveLength;
    fDirection.y = mouseMove.y / moveLength;
    fDirection.z = 0.0f;

    //�ړ��ʂ����Z
    transform_.rotate_.y += (fDirection.x) * 5.0f; // �������̉�]
    transform_.rotate_.x += (fDirection.y) * 5.0f; // �c�����̉�]

    //////////////////////////////////////�ł�����ρA�������������J�b�R�悭���������I


    /*//////////////////////////////////
    //�}�E�X�̈ړ��ʂ��擾
    XMFLOAT3 mouseMove = Input::GetMouseMove();

    //�ړ��x�N�g�����v�Z
    XMVECTOR moveVector = XMLoadFloat3(&mouseMove);

    //�����x�N�g���𐳋K��
    XMVECTOR normalizedDirection = XMVector3Normalize(moveVector);

    //���K�����ꂽ�����x�N�g�����擾
    XMFLOAT3 fDirection;
    XMStoreFloat3(&fDirection, normalizedDirection);

    //�ړ��ʂ����Z
    transform_.rotate_.y += (fDirection.x) * 5.0f; // �������̉�]
    transform_.rotate_.x += (fDirection.y) * 5.0f; // �c�����̉�]

    //////////////////////////////////////////////////�ꌩ�ǂ��������ǂ��߂ł����B�B*/

    ////�J�����̉�]
    XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y)); 

    //�J�����̈ʒu�Ɖ�]������
    XMMATRIX mView = mRotX * mRotY;

    //�v���C���[���W�擾
    Player* pPlayer = static_cast<Player*>(FindObject("Player"));
    plaPos_ = pPlayer->GetPlaPos();

    //�v���C���[�L�����N�^�[�̈ʒu���J�����̈ʒu�Ƃ���
    camPos.x = plaPos_.x;
    camPos.y = plaPos_.y + 2; //�ڐ�����
    camPos.z = plaPos_.z;

    //�J�����̈ʒu�Əœ_���擾
    XMVECTOR camPosVector = XMLoadFloat3(&camPos);
    XMVECTOR forwardVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    forwardVector = XMVector3TransformCoord(forwardVector, mView);
    XMStoreFloat3(&aimDirection_, forwardVector);   //�v���C���[�N���X�ɐi�s�����x�N�g��(float3)��`����p                    
    forwardVector = XMVectorAdd(camPosVector, forwardVector);

    //�J�����̈ʒu�Əœ_��ݒ�
    XMFLOAT3 camPosFloat3;
    XMFLOAT3 camTargetFloat3;
    XMStoreFloat3(&camPosFloat3, camPosVector);
    XMStoreFloat3(&camTargetFloat3, forwardVector);
    Camera::SetPosition(camPosFloat3);
    Camera::SetTarget(camTargetFloat3);

}

//�`��
void Aim::Draw()
{
    pNum->Draw(1520/2, 800/2, "+");
}

//�J��
void Aim::Release()
{
}
