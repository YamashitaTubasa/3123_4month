#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"

class Enemy {
public:
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw(ViewProjection* viewProjection);

public:
	// �I�u�W�F�N�g
	Object3d* obj = nullptr;
private:
	// ���f��
	Model* enemyModel = nullptr;
};
