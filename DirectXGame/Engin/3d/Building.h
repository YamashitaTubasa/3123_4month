#pragma once
#include "Object3d.h"

class Building : public Object3d
{
public:
	//デストラクタ
	~Building();
	//初期化
	bool BuildingInitialize();

	//リスト
	const std::list<std::unique_ptr<Building>>& GetBuildings() { return buildings_; }

private:

	//建物
	std::list<std::unique_ptr<Building>> buildings_;

	// モデル
	Model* buildingModel = nullptr;
};