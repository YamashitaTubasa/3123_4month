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
	void Update(Player* player_, std::vector<Vector3>& point);
	void ViewUpdate();

	void TitleR(Player* player_);

	void SetPlayer(Player* player_);
	void SetEye(Vector3 view);

	//�x�N�g�����擾
	void GetVec(Vector3 a, Vector3 b);

	ViewProjection* GetView() { return viewProjection; }
	bool GetIsEnd() { return isEnd; }

	Object3d* GetCamera() { return camera; }
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
	Spline splineCam;

	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };

	float timeRate;
	bool isEnd;
};

