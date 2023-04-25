#pragma once
#include "Object3d.h"

class Building : public Object3d
{
public:
	//�f�X�g���N�^
	~Building();
	//������
	bool BuildingInitialize();

	//���X�g
	const std::list<std::unique_ptr<Building>>& GetBuildings() { return buildings_; }

private:

	//����
	std::list<std::unique_ptr<Building>> buildings_;

	// ���f��
	Model* buildingModel = nullptr;
};