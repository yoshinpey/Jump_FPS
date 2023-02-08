#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

static const int FPS = 60;

//Timer�Ǘ�����N���X
class Timer : public GameObject
{
    int timer;
    Text* pText;
public:
    //�R���X�g���N�^
    Timer(GameObject* parent);

    //�f�X�g���N�^
    ~Timer();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void Start(float seconds);

    bool IaFinished();


};