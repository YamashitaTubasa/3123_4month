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
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw(ViewProjection* viewProjection);

	//fever�^�C��
	void GoesFever();
	bool GetFever() { return isFever; }
	int GetFeverNum() { return feverNum; }

	//�x�N�g�����擾
	void GetVec(Vector3 a, Vector3 b);
	float GetVal() { return val; }
	//�t���O
	bool GetOnRail() { return isOnRail; }
	void SetOnRail(bool isOnRail_) { this->isOnRail = isOnRail_; }

public:
	// �I�u�W�F�N�g
	Object3d* obj = nullptr;
private:
	Input* input_ = nullptr;
	// ���f��
	Model* playerModel = nullptr;
	//fever
	int feverTime;
	bool isFever = false;
	int feverNum = 0;
	float val = 1000.0f;
	//���[���ɏ���Ă�����
	bool isOnRail = false;
};