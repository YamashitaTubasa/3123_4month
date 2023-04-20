#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"
#include "Particle.h"

class Player : public Object3d
{
public:
	//デストラクタ
	~Player();
	//初期化
	bool PlayerInitialize();

	void Update()override;

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info) override;
	void OffCollision(const CollisionInfo& info) override;

	//フラグ
	bool GetOnRail() { return isOnRail; }
	void SetOnRail(bool isOnRail_) { this->isOnRail = isOnRail_; }
	bool GetIsHit() { return isHit; }
	void SetIsHit(bool isHit_) { this->isHit = isHit_; }

	//hp
	int GetHP() { return hp; }
	void SetHP(int hp_) { this->hp = hp_; }

private:
	Input* input = nullptr;
	// モデル
	Model* playerModel = nullptr;
	//パーティクル
	Particle* particle = nullptr;
	//HP
	int hp;
	//レールに乗っている状態
	bool isOnRail;
	//当たり判定
	bool isHit;
	int coolTime;
};
