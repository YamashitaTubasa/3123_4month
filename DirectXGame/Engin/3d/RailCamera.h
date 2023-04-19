#pragma once
#include "ViewProjection.h"
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Player.h"
#include "PlayerAttack.h"


class RailCamera {
public:
	//�C���X�^���X
	RailCamera();
	~RailCamera();
	//������
	void Initialize();
	//�X�V
	void Update(Player* player_,PlayerAttack* attack_, std::vector<Vector3>& point);

	//�x�N�g�����擾
	void GetVec(Vector3 a, Vector3 b);

	ViewProjection* GetView() { return viewProjection; }

	//fever�^�C��
	void GoesFever(Object3d* player_);

	bool GetFever() { return isFever; }

private:
	Input* input_ = nullptr;
	ViewProjection* viewProjection = nullptr;
	Object3d* camera = nullptr;
	Input* input = nullptr;
	//fever
	int feverTime;
	bool isFever = false;

	//�X�v���C��
	Spline spline_;

	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };

	float val;

	float timeRate;
};

