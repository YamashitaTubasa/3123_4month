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

	//hp
	int GetHP() { return hp; }
	void SetHP(int hp_) { this->hp = hp_; }

	//Getter
	bool GetIsPush() { return isPush; }
	float GetVal() { return val; }
	//fever
	void GoesFever();
	bool GetFever() { return isFever; }
	int GetFeverNum() { return feverNum; }
	const bool& GetIsBurst() { return isBurst; }
	void SetIsBurst(const bool& isBurst) { this->isBurst = isBurst; }

	bool GetGaugeAdd() { return isGauge_; }
	void SetGaugeAdd(bool isGauge) { this->isGauge_ = isGauge; }

private:
	Input* input = nullptr;
	// ���f��
	Model* playerModel = nullptr;
	//�p�[�e�B�N��
	Particle* particle = nullptr;
	//HP
	int hp;
	//���[���ɏ���Ă�����
	bool isOnRail;
	//�L�[����������
	bool isPush;
	int pushTime;
	//fever
	int feverTime;
	bool isFever;
	int feverNum;
	float val;
	//�����蔻��
	bool isHit;
	int coolTime;
	bool isBurst = false;

	bool isGauge_ = false;
};
