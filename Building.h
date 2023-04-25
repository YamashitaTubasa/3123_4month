#pragma once
#include "Object3d.h"

class Building : public Object3d
{
public:
	//�f�X�g���N�^
	~Building();
	//������
	bool BuildingInitialize();

	//�G���X�g
	const std::list<std::unique_ptr<Building>>& GetEnemys() { return buildings_; }

private:

	//�G
	std::list<std::unique_ptr<Building>> buildings_;

	// ���f��
	Model* buildingModel = nullptr;
};