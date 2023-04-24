#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Model.h"
#include "Player.h"

class PlayerAttack : public Object3d
{
public:
	//�f�X�g���N�^
	~PlayerAttack();
	//������
	bool AttackInitialize(Player* player_);

	void Update()override;

	//�Փˎ��R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info) override;
	void OffCollision(const CollisionInfo& info) override;

	//Getter
	bool GetIsPush() { return isPush; }
	float GetVal() { return val; }
	//fever
	void GoesFever();
	bool GetFever() { return isFever; }
	int GetFeverNum() { return feverNum; }

	const bool& GetIsDead() { return isDead; }
	void SetIsDead(const bool& isDead) { this->isDead = isDead; }

private:
	Input* input = nullptr;
	// ���f��
	Model* attackModel = nullptr;
	//�ϐ�
	bool isPush;
	int pushTime;
	//fever
	int feverTime;
	bool isFever;
	int feverNum;
	float val;
	//���[���ɏ���Ă�����
	bool isOnRail;
	//�����������̏����Ɏg���ϐ�
	bool isHit;
	int coolTime;
	bool isDead = false;
};
