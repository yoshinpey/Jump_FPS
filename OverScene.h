#pragma once
#include "Engine/GameObject.h"

//Over�V�[�����Ǘ�����N���X
class OverScene : public GameObject
{
	int hPict_;    //�摜�ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	OverScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};