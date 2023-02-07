#pragma once
#include "Engine/Text.h"
#include "Engine/GameObject.h"

//Score���Ǘ�����N���X
class Score : public GameObject
{
    Text* pText;
public:
    //�R���X�g���N�^
    Score(GameObject* parent);

    //�f�X�g���N�^
    ~Score();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};