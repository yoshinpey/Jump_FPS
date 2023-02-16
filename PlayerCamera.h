#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"


//��l�����Ǘ�����N���X
class PlayerCamera : public GameObject
{
    int hModel_;            //���f���ԍ�
    XMFLOAT3 fPoint, fPoint2, fMove;
    float PlaPosX_, PlaPosY_, PlaPosZ_;
    XMFLOAT3 camPos;
    Text* pNum;
public:
    //�R���X�g���N�^
    PlayerCamera(GameObject* parent);

    //�f�X�g���N�^
    ~PlayerCamera();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};