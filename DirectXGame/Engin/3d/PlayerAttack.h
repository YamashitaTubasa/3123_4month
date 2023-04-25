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
	bool GetGaugeAdd() { return isGauge_; }

	//fever
	void GoesFever();
	bool GetFever() { return isFever; }
	int GetFeverNum() { return feverNum; }
	const bool& GetIsDead() { return isDead; }
	void SetIsDead(const bool& isDead) { this->isDead = isDead; }


	void SetGaugeAdd(bool isGauge) { this->isGauge_ = isGauge; }

private:
	Input* input = nullptr;
	// モデル
	Model* attackModel = nullptr;
	//変数
	bool isPush;
	int pushTime;
	//fever
	int feverTime;
	bool isFever;
	int feverNum;
	float val;
	//レールに乗っている状態
	bool isOnRail;
	//当たった時の処理に使う変数
	bool isHit;
	int coolTime;

	bool isGauge_ = false;

	bool isDead = false;

};
