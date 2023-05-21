#include "Building.h"

Building::~Building()
{
	delete builModel01;
	delete builModel02;
	delete builModel03;
	for (int i = 0; i < 5; i++)
	{
		delete buil_01[i];
		delete buil_02[i];
		delete buil_03[i];
	}
}

bool Building::BuildingInitialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	// OBJからモデルデータを読み込む
	builModel01 = Model::LoadFromOBJ("building_01");
	builModel02 = Model::LoadFromOBJ("building_02");
	builModel03 = Model::LoadFromOBJ("building_03");

	//建物
	for (int i = 0; i < 5; i++)
	{
		buil_01[i] = Object3d::Create();
		buil_02[i] = Object3d::Create();
		buil_03[i] = Object3d::Create();
		// オブジェクトにモデルをひも付ける
		buil_01[i]->SetModel(builModel01);
		buil_01[i]->SetScale(Vector3({ 10, 10, 10 }));
		buil_02[i]->SetModel(builModel02);
		buil_02[i]->SetScale(Vector3({ 20, 20, 20 }));
		buil_03[i]->SetModel(builModel03);
		buil_03[i]->SetScale(Vector3({ 10, 10, 10 }));
	}
	buil_02[0]->SetPosition(Vector3(200, -60, -750));
	buil_02[1]->SetPosition(Vector3(-350, -60, -575));
	buil_02[2]->SetPosition(Vector3(-200, -60, -100));
	buil_02[3]->SetPosition(Vector3(170, -60, 200));
	buil_02[4]->SetPosition(Vector3(-200, -60, 600));

	buil_03[0]->SetPosition(Vector3(70, -60, -750));
	buil_03[1]->SetPosition(Vector3(-175, -60, -575));
	buil_03[2]->SetPosition(Vector3(-360, -60, -375));
	buil_03[3]->SetPosition(Vector3(70, -60, 200));
	buil_03[4]->SetPosition(Vector3(-100, -60, 600));

	return true;
}

void Building::Update()
{
	for (int i = 0; i < 5; i++)
	{
		buil_01[i]->Update();
		buil_02[i]->Update();
		buil_03[i]->Update();
	}
}

void Building::Draw(RailCamera* railCamera)
{
	for (int i = 0; i < 5; i++)
	{
		/*buil_01[i]->Draw(railCamera->GetView());*/
		buil_02[i]->Draw(railCamera->GetView());
		buil_03[i]->Draw(railCamera->GetView());
	}
}
