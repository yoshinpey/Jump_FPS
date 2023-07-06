#include "Engine/Camera.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Aim.h"
#include "Player.h"
#include "Gauge.h"


/*
<��邱�ƃ��X�g>
�W�F�b�g�p�b�N�̃R�[�h�������邩�璼��
�ʏ�W�����v�ƃW�F�b�g�p�b�N�̊|�����킹
�����Ƒ���ɉ�����t����
�ړ����͂���߂��Ƃ��s�^�b�Ǝ~�܂�̒�������

�X�N���[���̍��W�擾�ŃX�N���[���T�C�Y���f�B�X�v���C���Ƃɍ��킹����
*/

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),
    gravity_(-9.81), fuel_(50),coolTime_(0), CanJump_(false), acceleration_(0),
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
    //Jump();           //�W�����v�A�N�V����
    JetPack();        //�W�F�b�g�p�b�N
    //BoostJump();        //�u�[�X�g�W�����v
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
    pNum->Draw(50, 200, "fuel");
    pNum->Draw(50, 250, fuel_);
    pNum->Draw(50, 400, "coolTime");
    pNum->Draw(50, 450, coolTime_);

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

//���_
void Player::CameraPosition()
{
#if 0
    //�e�X�g�p�̃J����
    XMFLOAT3 camPos{ 0, 10, -20 };
    XMFLOAT3 camTag{ 0, 0, 0 };
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTag);
#endif
}


// �v���C���[�̈ړ�
void Player::Move()
{
    // �ړ�
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);

    // �G�C�����Ăяo��
    Aim* pAim = (Aim*)FindObject("Aim");
    XMFLOAT3 aimDirection = pAim->GetAimDirection();

    // Player�N���X��Move�֐����̈ꕔ
    if (Input::IsKey(DIK_W)) {
        fMove.x += aimDirection.x;
        fMove.z += aimDirection.z;
    }
    if (Input::IsKey(DIK_A)) {
        fMove.x -= aimDirection.z;
        fMove.z += aimDirection.x;
    }
    if (Input::IsKey(DIK_S)) {
        fMove.x -= aimDirection.x;
        fMove.z -= aimDirection.z;
    }
    if (Input::IsKey(DIK_D)) {
        fMove.x += aimDirection.z;
        fMove.z -= aimDirection.x;
    }

    // ���K������
    float moveLength = sqrtf(fMove.x * fMove.x + fMove.z * fMove.z);
    if (moveLength != 0)
    {
        fMove.x /= moveLength;
        fMove.z /= moveLength;
    }

    // ���x�̐���
    float walkSpeed = 0.2f;         // ���s���x
    float runSpeed = 0.4f;          // ���s���x
    float nowSpeed = 0;             // �������x

    // �ړ����͂����邩�ǂ���
    bool isMoving = Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D);

    // �ړ����͂���
    if (isMoving)
    {
        // �����Ă��邩�ǂ���
        if (Input::IsKey(DIK_LSHIFT))
        {
            nowSpeed = runSpeed;    // ���葬�x��ݒ�
        }
        else
        {
            nowSpeed = walkSpeed;   // �������x��ݒ�
        }
    }
    else
    {
        // �e�ړ��{�^���𗣂����Ƃ��ɑ��x�����Z�b�g
        nowSpeed = 0.0f;
    }

    // �ړ��ɔ��f
    transform_.position_.x += fMove.x * nowSpeed;
    transform_.position_.z += fMove.z * nowSpeed;
}


#if 0
void Player::BoostJump()
{
    ///////////�Ƃ肠�����̍\�z////////////////////
    static int jumpCount = 0;              // �W�����v��
    if (Input::IsKey(DIK_SPACE))            // �W�����v�L�[�������ꂽ�ꍇ
    {
        if (jumpCount == 0)                 // �W�����v�񐔂�0�̏ꍇ�i�ʏ�̃W�����v�j
        {
            // �ʏ�̃W�����v����
            Jump();
            jumpCount = 1;                  // �W�����v�񐔂�1�ɐݒ�
        }
        else if (jumpCount == 1)            // �W�����v�񐔂�1�̏ꍇ�i�u�[�X�g�W�����v�j
        {
            // �u�[�X�g�W�����v����
            JetPack();
            jumpCount = 0;                  // �W�����v�񐔂����Z�b�g
        }
    }
    // �n�ʂɒ��n�����ꍇ�̏���
    if (transform_.position_.y <= 0)
    {
        transform_.position_.y = 0;
    }
}
#endif

#if 0
void Player::BoostJump()
{
    ///////////////�H����////////////////////
    float velocity = 5.0f;          // �����x
    float gravity = -9.8f;          // �d�͉����x
    float deltaTime = 0.019f;       // �K���Ȃ����������l

    static bool canJump = true;     // �W�����v�\�ȏ�Ԃ��ǂ���
    static float jumpTime = 0.0f;   // �W�����v�o�ߎ���

    if (Input::IsKeyDown(DIK_SPACE) && canJump) //�W�����v�L�[��������Ă���A�W�����v�\�ȏꍇ
    {
        jumpTime = 0.0f;
        canJump = false;  //�A���W�����v��h�~���邽�߁A�W�����v���̓W�����v�t���O�𖳌���
    }

    if (!canJump)
    {
        //�W�����v���Ă���̎��Ԃ̌o��
        jumpTime += deltaTime;

        //���������グ�^��    y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * jumpTime + 0.5f * gravity * jumpTime * jumpTime;
        transform_.position_.y = pos;

        //�d�͂ɂ�闎��
        velocity += gravity * deltaTime;

        //�n�ʂɒ��n�����Ƃ�
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;
            canJump = true;  // �n�ʂɒ��n������W�����v�\�ɂ���
        }
    }
}
#endif

void Player::JetPack()
{
    float gravity = -9.81;      // �d��
    float delta = 0.02f;        // �K���Ȃ����������l

    float fuel_ = 50;            // �R��
    float coolTime = 0;         // �N�[���^�C��
    float acceleration_ = 0.3f;     // ��s�����x
    float velocity = 0.0f;      // �����x

    float flightTime = 0;       // �؋󒆂̎��Ԍo��

    // �n�ʂɂ���Ƃ�
    if (transform_.position_.y <= 0)
    {
        flightTime = 0;         // �؋󂵂ĂȂ�
    }
    else
    {
        // ���R����
        transform_.position_.y += gravity * delta;
        flightTime++;
    }

    // �R����0���傫�����̓W�����v�\
    if (fuel_ > 0)
    {
        // �W�����v����
        if (Input::IsKey(DIK_SPACE))
        {
            velocity = acceleration_ * flightTime;
            transform_.position_.y += velocity * delta;     // �ʒu�������x*�o�ߎ���
            fuel_--;     // �R�������炷
        }
        else
        {
            flightTime = 0;     // �L�[���͂��Ȃ���Ή��������Z�b�g
            velocity = 0;
        }
    }

    // �W�����v�s�\--�R�����J���ł��n�ʂɂ���
    if (transform_.position_.y <= 0 && fuel_ <= 0)
    {
        transform_.position_.y = 0;
        if (coolTime <= 0) coolTime += 30;             // �킸���ȉ񕜑ҋ@���Ԃ�p��
    }

    // �N�[���^�C�����c���Ă�����0�ɂȂ�܂Ō��炷
    if (coolTime > 0)
        coolTime--;
    else
        if (fuel_ < 50) fuel_++;          // �R�����ő�l�܂ŉ�
}



//�W�����v
void Player::Jump()
{
    float velocity = 5.0f;          // �����x
    float delta = 0.02f;       // �K���Ȃ����������l
    float gravity = 9.81;
    static bool canJump = true;     // �W�����v�\�ȏ�Ԃ��ǂ���
    static float flightTime = 0.0f;   // �W�����v�o�ߎ���

    if (Input::IsKeyDown(DIK_SPACE) && canJump) //�W�����v�L�[��������Ă���A�W�����v�\�ȏꍇ
    {
        flightTime = 0.0f;
        canJump = false;  //�A���W�����v��h�~���邽�߁A�W�����v���̓W�����v�t���O�𖳌���
    }

    if (!canJump)
    {
        //�W�����v���Ă���̎��Ԃ̌o��
        flightTime += delta;
        
        //���������グ�^��    y  =  v_0  *  t  -  0.5  *  g  *  t^2
        float pos = velocity * flightTime + 0.5f * gravity * flightTime * flightTime;
        transform_.position_.y = pos;

        //�d�͂ɂ�闎��
        velocity += gravity * delta;

        //�n�ʂɒ��n�����Ƃ�
        if (transform_.position_.y <= 0)
        {
            transform_.position_.y = 0;//�O�̂��ߒn�ʂɍ��킹��
            canJump = true;  // �n�ʂɒ��n������W�����v�\�ɂ���
        }
    }
}