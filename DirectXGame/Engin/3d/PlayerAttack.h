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

private:
	Input* input = nullptr;
	// ���f��
	Model* attackModel = nullptr;
	//�ϐ�
	bool isPush;
	int pushTime;
	//fever
	int feverTime;
	bool isFever = false;
	int feverNum = 0;
	float val = 1000.0f;
	//���[���ɏ���Ă�����
	bool isOnRail = false;
	//�����������̏����Ɏg���ϐ�
	bool isHit = false;
	int coolTime;
};
