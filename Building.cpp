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

	// OBJからモデルデータを読み込む
	buildingModel = Model::LoadFromOBJ("fighter");
	// 3Dオブジェクト生成
	Create();

	return true;
}
