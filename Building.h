#pragma once
#include "Object3d.h"

class Building : public Object3d
{
public:
	//デストラクタ
	~Building();
	//初期化
	bool BuildingInitialize();

	//敵リスト
	const std::list<std::unique_ptr<Building>>& GetEnemys() { return buildings_; }

private:

	//敵
	std::list<std::unique_ptr<Building>> buildings_;

	// モデル
	Model* buildingModel = nullptr;
};