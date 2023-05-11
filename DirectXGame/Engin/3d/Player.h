#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"
#include "Particle.h"
#include "MathFunc.h"


class Player : public Object3d
{
public:
	//レールの位置
	enum RailPosition
	{
		LEFT, //左
		MIDDLE,  //中央
		RIGHT,  //右
	};
public:
	//デストラクタ
	~Player();
	//初期化
	bool PlayerInitialize();

	void Update(std::vector <Vector3>& point);

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
	bool GetIsAttack() { return isAttack; }
	int GetAttackNum() { return attackNum; }
	float GetAttackTime() { return attackTime; }
	float GetVal() { return val; }
	//fever
	void GoesFever();
	bool GetFever() { return isFever; }
	int GetFeverNum() { return feverNum; }
	const bool& GetIsBurst() { return isBurst; }
	void SetIsBurst(const bool& isBurst) { this->isBurst = isBurst; }

	bool GetGaugeAdd() { return isGauge_; }
	void SetGaugeAdd(bool isGauge) { this->isGauge_ = isGauge; }

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
	//移動しているか
	bool isMove;

	//キーを押したか
	bool isPush;
	int pushTime;
	bool isAttack;
	float attackTime;
	//攻撃
	int attackNum;
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

	float start = 0.0;
	float end = 360.0;

	//自機の位置
	int railPos = MIDDLE;
};
