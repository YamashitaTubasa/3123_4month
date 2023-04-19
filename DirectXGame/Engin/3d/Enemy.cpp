#include "Enemy.h"
#include "GamePlayScene.h"
#include "string.h"

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
	const char* str1 = "class Player";
	const char* str2 = "class PlayerAttack";

	//相手がplayer
	if (strcmp(toCollisionName, str1) == 0) {

	}

	//相手がplayerの攻撃
	if (strcmp(toCollisionName, str2) == 0) {
		if (isDead_ == false)
		{
			isDead_ = true;
		}
	}
}

void Enemy::OffCollision(const CollisionInfo& info)
{

}