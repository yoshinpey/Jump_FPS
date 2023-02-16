#pragma once
#include "Engine/GameObject.h"

//HP���Ǘ�����N���X
class Gauge : public GameObject
{
    int hpPict_[2];    //�摜�ԍ�
    int maxHp_, nowHp_;
public:
    //�R���X�g���N�^
    Gauge(GameObject* parent);

    //�f�X�g���N�^
    ~Gauge();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //HP�Z�b�^�[
    void SetHp(int maxHp, int nowHp)
    {
        maxHp_ = maxHp;
        nowHp_ = nowHp;
    }
};