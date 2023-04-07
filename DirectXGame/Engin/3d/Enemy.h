#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"

class Enemy {
public:
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw(ViewProjection* viewProjection);

public:
	// オブジェクト
	Object3d* obj = nullptr;
private:
	// モデル
	Model* enemyModel = nullptr;
};
