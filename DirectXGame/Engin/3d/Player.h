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

	//Getter
	bool GetIsPush() { return isPush; }
	float GetVal() { return val; }
	//fever
	void GoesFever();
	bool GetFever() { return isFever; }
	int GetFeverNum() { return feverNum; }
	const bool& GetIsBurst() { return isBurst; }
	void SetIsBurst(const bool& isBurst) { this->isBurst = isBurst; }

	bool GetGaugeAdd() { return isGauge_; }
	void SetGaugeAdd(bool isGauge) { this->isGauge_ = isGauge; }

	//イージング
	//t:時間 b:開始位置 c:開始位置-終了位置の差 d:合計時間
	float ease_in(float t, float b, float c,float d);

	float ease_in_cubic(float x);
	int GetDivide() { return speedUpCount; }

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
	//キーを押したか
	bool isPush;
	int pushTime;
	bool isAttack;
	int attackTime;
	//fever
	int feverTime;
	bool isFever;
	int feverNum;
	float val;

	int speedUpCount = 3;
	float res = 0.0f;
	//当たり判定
	bool isHit;
	int coolTime;
	bool isBurst = false;

	bool isGauge_ = false;

};
