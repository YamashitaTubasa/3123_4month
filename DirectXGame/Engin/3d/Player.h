#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"
#include "Particle.h"

class Player : public Object3d
{
public:
	//�f�X�g���N�^
	~Player();
	//������
	bool Initialize() override;
	//�X�V
	void Update() override;
	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info) override;

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
	bool GetIsHit() { return isHit; }

public:
	// �I�u�W�F�N�g
	Object3d* obj = nullptr;
private:
	Input* input = nullptr;
	// ���f��
	Model* playerModel = nullptr;
	//�p�[�e�B�N��
	Particle* particle = nullptr;
	//fever
	int feverTime;
	bool isFever = false;
	int feverNum = 0;
	float val = 1000.0f;
	//���[���ɏ���Ă�����
	bool isOnRail = false;
	//�����蔻��
	bool isHit = false;
};
