#include "Building.h"

Building::~Building()
{
	delete buildingModel01;
	delete buildingModel02;
	delete buildingModel03;
}

bool Building::BuildingInitialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	// OBJ���烂�f���f�[�^��ǂݍ���
	/*buildingModel01 = Model::LoadFromOBJ("building_01");
	buildingModel02 = Model::LoadFromOBJ("building_02");*/
	buildingModel03 = Model::LoadFromOBJ("building_03");

	// 3D�I�u�W�F�N�g����
	Create();

	return true;
}
