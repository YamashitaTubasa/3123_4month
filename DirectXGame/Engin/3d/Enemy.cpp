#include "Enemy.h"
#include "GamePlayScene.h"

//デストラクタ
Enemy::~Enemy() {
	delete enemyModel;
	delete obj;
}

//初期化
void Enemy::Initialize(const Vector3& v)
{
	// OBJからモデルデータを読み込む
	enemyModel = Model::LoadFromOBJ("ironSphere");
	// 3Dオブジェクト生成
	obj = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	obj->SetModel(enemyModel);
	obj->SetPosition(Vector3(v.x, v.y, v.z));
}

//更新
void Enemy::Update() {
	//更新
	obj->Update();
}

//描画
void Enemy::Draw(ViewProjection* viewProjection) {
	obj->Draw(viewProjection);
}