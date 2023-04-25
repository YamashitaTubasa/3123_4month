#include "Building.h"

Building::~Building()
{
	delete buildingModel;
}

bool Building::BuildingInitialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	// OBJ���烂�f���f�[�^��ǂݍ���
	buildingModel = Model::LoadFromOBJ("fighter");
	// 3D�I�u�W�F�N�g����
	Create();

	return true;
}
