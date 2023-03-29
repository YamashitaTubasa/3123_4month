#pragma once
#include "ViewProjection.h"
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"


class RailCamera {
public:
	//�C���X�^���X
	RailCamera();
	~RailCamera();
	//������
	void Initialize(Object3d* player_);
	//�X�V
	void Update(Object3d* player_, std::vector<Vector3>& point);

	//���ʃx�N�g�����擾
	Vector3 GetFront(Vector3 a, Vector3 b);

	ViewProjection* GetView() { return viewProjection; }

private:
	ViewProjection* viewProjection = nullptr;
	Object3d* camera = nullptr;
	Input* input = nullptr;
	enum rane {
		LEFT,
		MID,
		RIGHT
	};
	rane raneNum = MID;
	float velo;
	Vector3 angle = { 0,0,0 };


	//�X�v���C��
	Spline spline_;

	float timeRate;
};

