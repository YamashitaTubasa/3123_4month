#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>

//GameSceneの前方宣言
class GamePlayScene;

class Enemy {
public:
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize(const Vector3& v);
	//更新
	void Update();
	//描画
	void Draw(ViewProjection* viewProjection);

	//敵リスト
	const std::list<std::unique_ptr<Enemy>>& GetEnemys() { return enemys_; }

	//gameSceneのsetter
	void SetGameScene(GamePlayScene* gameScene) { gameScene_ = gameScene; }

	bool IsDead() const { return isDead_; }

public:
	// オブジェクト
	Object3d* obj = nullptr;

private:
	//ゲームシーン
	GamePlayScene* gameScene_ = nullptr;

	//デスフラグ
	bool isDead_ = false;

	//敵
	std::list<std::unique_ptr<Enemy>> enemys_;

	// モデル
	Model* enemyModel = nullptr;

	//半径
	float radius = 1.0f;
};
