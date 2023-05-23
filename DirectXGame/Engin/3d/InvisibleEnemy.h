#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>

//GameSceneの前方宣言
class GamePlayScene;


class InvisibleEnemy : public Object3d
{
public:
	//デストラクタ
	~InvisibleEnemy();
	//初期化
	void InvEnemyInitialize();

	//敵リスト
	const std::list<std::unique_ptr<InvisibleEnemy>>& GetInvEnemys() { return invEnemys_; }

	//gameSceneのsetter
	void SetGameScene(GamePlayScene* gameScene) { gameScene_ = gameScene; }
private:
	//ゲームシーン
	GamePlayScene* gameScene_ = nullptr;
	//敵
	std::list<std::unique_ptr<InvisibleEnemy>> invEnemys_;

	// モデル
	Model* invEnemyModel = nullptr;

	//半径
	float radius = 1.0f;
};

