#include "Enemy.h"
#include "GamePlayScene.h"

//デストラクタ
Enemy::~Enemy() {
	delete enemyModel;
}

//初期化
void Enemy::EnemyInitialize(const Vector3& v)
{
	Initialize();
	// OBJからモデルデータを読み込む
	enemyModel = Model::LoadFromOBJ("ironSphere");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(enemyModel);
	SetPosition(Vector3(v.x, v.y, v.z));
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	if (isDead_ == false)
	{
		isDead_ = true;
	}
}
