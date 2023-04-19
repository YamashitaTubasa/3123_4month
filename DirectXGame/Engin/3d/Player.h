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
	bool PlayerInitialize();

	void Update()override;

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info) override;
	void OffCollision(const CollisionInfo& info) override;

	//�t���O
	bool GetOnRail() { return isOnRail; }
	void SetOnRail(bool isOnRail_) { this->isOnRail = isOnRail_; }
	bool GetIsHit() { return isHit; }
	void SetIsHit(bool isHit_) { this->isHit = isHit_; }

private:
	Input* input = nullptr;
	// ���f��
	Model* playerModel = nullptr;
	//�p�[�e�B�N��
	Particle* particle = nullptr;
	//���[���ɏ���Ă�����
	bool isOnRail = false;
	//�����蔻��
	bool isHit = false;
	int coolTime;
};
