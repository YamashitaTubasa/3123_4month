#include "Enemy.h"

//デストラクタ
Enemy::~Enemy() {
	delete enemyModel;
	delete obj;
}

//初期化
void Enemy::Initialize() {
	// OBJからモデルデータを読み込む
	enemyModel = Model::LoadFromOBJ("sphere");
	// 3Dオブジェクト生成
	obj = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	obj->SetModel(enemyModel);
	obj->SetRotation(Vector3({ 0, 90, 0 }));
	obj->SetPosition(Vector3(0, 0, -790));

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