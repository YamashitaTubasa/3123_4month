#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Model.h"
#include "Player.h"

class PlayerAttack : public Object3d
{
public:
	//デストラクタ
	~PlayerAttack();
	//初期化
	bool AttackInitialize(Player* player_);

	void Update()override;

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info) override;
	void OffCollision(const CollisionInfo& info) override;

	//Getter
	bool GetIsPush() { return isPush; }
	float GetVal() { return val; }
	//fever
	void GoesFever();
	bool GetFever() { return isFever; }
	int GetFeverNum() { return feverNum; }

private:
	Input* input = nullptr;
	// モデル
	Model* attackModel = nullptr;
	//変数
	bool isPush;
	int pushTime;
	//fever
	int feverTime;
	bool isFever = false;
	int feverNum = 0;
	float val = 1000.0f;
	//レールに乗っている状態
	bool isOnRail = false;
	//当たった時の処理に使う変数
	bool isHit = false;
	int coolTime;
};
