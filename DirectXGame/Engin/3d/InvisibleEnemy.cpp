#include "InvisibleEnemy.h"
#include "GamePlayScene.h"

InvisibleEnemy::~InvisibleEnemy()
{
	delete invEnemyModel;
}

void InvisibleEnemy::InvEnemyInitialize()
{
	Initialize();
	// OBJからモデルデータを読み込む
	invEnemyModel = Model::LoadFromOBJ("ironSphere_02");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(invEnemyModel);
}
