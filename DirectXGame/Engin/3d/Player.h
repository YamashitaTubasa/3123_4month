#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"

class Player {
public:
	//�f�X�g���N�^
	~Player();
	//������
	void Initialize(Model* model);
	//�X�V
	void Update();
	//�`��
	void Draw(ViewProjection* viewProjection);

	//fever�^�C��
	void GoesFever();
	bool GetFever() { return isFever; }

	//�x�N�g�����擾
	void GetVec(Vector3 a, Vector3 b);
	float GetVal() { return val; }

public:
	// �I�u�W�F�N�g
	Object3d* obj = nullptr;
private:
	// ���f��
	Model* playerModel = nullptr;
	//fever
	int feverTime;
	bool isFever = false;
	float val = 1000.0f;

	//�ړ��p�����x�N�g��
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };
};
