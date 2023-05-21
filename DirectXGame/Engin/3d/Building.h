#pragma once
#include "Object3d.h"
#include "RailCamera.h"

class Building : public Object3d
{
public:
	//�f�X�g���N�^
	~Building();
	//������
	bool BuildingInitialize();

	void Update();

	void Draw(RailCamera* railCamera);

private:
	// ���f��
	Model* builModel01;
	Model* builModel02;
	Model* builModel03;
	Model* ringModel;

	Object3d* buil_01[5];
	Object3d* buil_02[5];
	Object3d* buil_03[5];
	Object3d* ring[5];

	RailCamera* railCamera;
};